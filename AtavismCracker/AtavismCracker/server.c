#include "mongoose.h"

//Create by Kaotic on 06-12-15.

static const char *s_http_port = "80";
static struct mg_serve_http_opts s_http_server_opts;
static const char *host_path = "C:/Windows/System32/drivers/etc/hosts";

static void AtavismLogin(struct mg_connection *nc) {

	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
	mg_printf_http_chunk(nc, "Done,Pro (Cracked by Kaotic),http://kaotic.fr/AtavismCracker");
	mg_send_http_chunk(nc, "", 0);
}

static void CrackAuthor(struct mg_connection *nc) {

	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
	mg_printf_http_chunk(nc, "Kaotic");
	mg_send_http_chunk(nc, "", 0);
}

static void CrackVersion(struct mg_connection *nc) {

	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
	mg_printf_http_chunk(nc, "v0.9");
	mg_send_http_chunk(nc, "", 0);
}

static void CrackNormalOut(struct mg_connection *nc) {

	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\nContent-Type: text/html\r\n\r\n");
	mg_printf_http_chunk(nc, "AtivismCracker v0.9 by <a href=\"http://kaotic.fr/\">Kaotic</a><br>Update : 12 - 06 - 15");
	mg_send_http_chunk(nc, "", 0);
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
	struct http_message *hm = (struct http_message *) p;

	switch (ev) {
	case MG_EV_HTTP_REQUEST:
		if (mg_vcmp(&hm->uri, "/atavism/login.php") == 0) {
			AtavismLogin(nc);
			printf("Connection authorized to login!\n");
		}
		else if (mg_vcmp(&hm->uri, "/author") == 0) {
			CrackAuthor(nc);
		}
		else if (mg_vcmp(&hm->uri, "/version") == 0) {
			CrackVersion(nc);
		}
		else {
			CrackNormalOut(nc);
			printf("Connection Detected!\n");
			//mg_serve_http(nc, hm, s_http_server_opts);
		}
		break;
	default:
		break;
	}
}

int main(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  cs_stat_t st;


  mg_mgr_init(&mgr, NULL);
  nc = mg_bind(&mgr, s_http_port, ev_handler);
  if (nc == NULL) {
    fprintf(stderr, "AtavismCracker - Cannot bind port to %s\n", s_http_port);
    exit(1);
  }

  mg_set_protocol_http_websocket(nc);
  s_http_server_opts.document_root = "web_root";

  printf("AtavismCracker v0.9 created by Kaotic (http://kaotic.fr/).\n\n");
  printf("Starting AtavismCracker wait..\n");
  
  FILE *fd = fopen(host_path, "a");
  sleep(1);
  printf("Wait please..\n");
  fprintf(fd, "127.0.0.1 neojac.com\n");
  sleep(2);
  printf("Wait please....\n");
  fprintf(fd, "127.0.0.1 www.neojac.com\n");
  fclose(fd);
  sleep(1);
  printf("Wait please......\n");

  printf("AtavismCracker by Kaotic started !!\n");

  printf("Now you can login to AtavismOnline !\n");

  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);

  return 0;
}
