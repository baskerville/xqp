#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <err.h>
#include <xcb/xcb.h>

int main(int argc, char *argv[])
{
	int ret = EXIT_SUCCESS;
	int opt;

	while ((opt = getopt(argc, argv, "hv")) != -1) {
		switch (opt) {
			case 'h':
				printf("xqp [-h|-v] [WID ...]\n");
				return EXIT_SUCCESS;
				break;
			case 'v':
				printf("%s\n", VERSION);
				return EXIT_SUCCESS;
				break;
		}
	}

	int num = argc - optind;
	char **args = argv + optind;

	xcb_connection_t *dpy = xcb_connect(NULL, NULL);
	if (xcb_connection_has_error(dpy)) {
		errx(1, "Can't open display.\n");
	}

	xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(dpy)).data;
	if (screen == NULL) {
		errx(1, "Can't acquire screen.\n");
	}

	xcb_window_t root = screen->root;
	xcb_query_pointer_reply_t *qpr = xcb_query_pointer_reply(dpy, xcb_query_pointer(dpy, root), NULL);
	
	if (qpr != NULL) {
		if (num > 0) {
			ret = EXIT_FAILURE;
			for (int i = 0; i < num; i++) {
				xcb_window_t win = strtoul(args[i], NULL, 0);
				if (qpr->child == win) {
					ret = EXIT_SUCCESS;
					break;
				}
			}
		} else {
			printf("0x%08x\n", qpr->child);
		}
	} else {
		ret = EXIT_FAILURE;
	}

	free(qpr);
	xcb_disconnect(dpy);
	return ret;
}
