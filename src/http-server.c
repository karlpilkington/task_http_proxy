/*
 * =====================================================================================
 *
 *       Filename:  http_server.c
 *
 *    Description:  receive POST and RESPONE it
 *
 *        Version:  1.0
 *        Created:  11/29/2011 11:23:03 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YueYang (feinno), yueyang@feinno.com
 *        Company:  FCT
 *
 * =====================================================================================
 */

#include "http-server.h"

int
task_http_proxy(void) {
    struct event_base *base;
    struct evhttp *http;
    struct evhttp_bound_socket *handle;

    unsigned short port = PORT;

    log_write(INFO, "http-server: http proxy initialize.\n");

    /* As you konw */
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        return (1);

    if (signal(SIGCHLD, sig_chld) == SIG_ERR)
        return (1);

    /* Create a new base evObject */
    base = event_base_new();
    if (!base) {
        log_write(ERROR, "http-server: Couldn't create an event_base: exiting\n");
        return 1;
    }

    /* Create a new evhttp object to handle requests. */
    http = evhttp_new(base);
    if (!http) {
        log_write(ERROR, "http-server: Couldn't create evhttp. Exiting.\n");
        return 1;
    }

    /*
     * The path /post support post method
     * Receive shell command by post body
     */
    evhttp_set_cb(http, "/post", post_command_cb, NULL);

    /* We want to accept arbitrary requests, so we need to set a "generic"
     * cb.  We can also add callbacks for specific paths. */
    evhttp_set_gencb(http, other_cb, NULL);

    /* Now we tell the evhttp what port to listen on */
    handle = evhttp_bind_socket_with_handle(http, "0.0.0.0", port);

    if (!handle) {
        log_write(ERROR, "http-server: Couldn't bind to port %d. Exiting.\n", (int)port);
        return 1;
    }

    log_write(INFO, "http-server: http proxy initialized done.\n");
    event_base_dispatch(base);

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

static void
other_cb(struct evhttp_request *req, void *arg) {
    log_write(WARN, "http-server: Not Suppost this Path\n");
    evhttp_send_reply(req, 401, "olo", NULL);
    return;
}

static void
post_command_cb(struct evhttp_request *req, void *arg) {
    size_t sz;
    int buffer_sz;
    struct evbuffer *buf;
    char *buffer = NULL;
    pid_t pid;

    log_write(INFO, "http-server: POST command cb\n");

    if (EVHTTP_REQ_POST != evhttp_request_get_command(req)) {
        log_write(WARN, "http-server: Not support this method.\n");
        evhttp_send_reply(req, 500, "not support this method", NULL);
        return;
    }
    log_write(INFO, "http-server: POST Request.\n");

    buf = evhttp_request_get_input_buffer(req);
    sz = evbuffer_get_length(buf);

    buffer = malloc(sz + 1);
    if (NULL == buffer) {
        log_write(ERROR, "http-server: alloc memory error.\n");
        evhttp_send_reply(req, 500, "alloc memroy error", NULL);
        return ;
    }

    /* Init temp buffer */
    memset(buffer, 0, sz + 1);
    buffer_sz = evbuffer_remove(buf, buffer, sz);
    if (sz != buffer_sz) {
        log_write(ERROR, "http-server: post content error. sz: %ld, buffer_sz:%ld\n", sz, buffer_sz);
        evhttp_send_reply(req, 501, "post content error", NULL);
        free(buffer);
        buffer = NULL;

        return ;
    }

    /* NEED parser POST body and executed it */
    int execrc = shell_cmd(buffer);
    if (0 == execrc) {
        log_write(INFO, "http-server: reply 200 OK. %d\n", execrc);
        evhttp_send_reply(req, 200, "OK", NULL);
    } else {
        log_write(ERROR, "fork error. %d\n", execrc);
        evhttp_send_reply(req, 502, "ERR", NULL);
    }

    free(buffer);
    buffer = NULL;

    return ;
}
static void 
sig_chld(int signo) {
    pid_t pid;
    int chldst;
    if (signal(SIGCHLD, sig_chld) == SIG_ERR)
        return ;
    while (pid = waitpid(-1, &chldst, WNOHANG) > 0) {
        log_write(INFO, "in loop, pid: %d\n", pid);
        ;
    }

    if (chldst != 0) {
        log_write(ERROR, "child process terminated error, pid: %d, status: %d\n", pid, chldst);
    } else {
        log_write(INFO, "child process normal terminated, pid: %d, status: %d\n", pid, chldst);
    }

    return ;
}
