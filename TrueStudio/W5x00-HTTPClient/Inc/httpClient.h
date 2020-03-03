/*
 * httpClient.h
 *
 *  Created on: Feb 21, 2020
 *      Author: becky
 */

#ifndef HTTPCLIENT_H_
#define HTTPCLIENT_H_

#include <stdint.h>


// HTTP client debug message enable
#define _HTTPCLIENT_DEBUG_

// Data buffer size
#ifndef DATA_BUF_SIZE
	#define DATA_BUF_SIZE           2048
#endif

#define HTTP_CLIENT_PORT_MIN   0xB000 // 45056
#define HTTP_CLIENT_PORT_MAX   0xFFFF // 65535

/*********************************************
* HTTP Method String
*********************************************/
#define HTTP_GET                    "GET"
#define HTTP_HEAD                   "HEAD"
#define HTTP_POST                   "POST"
#define HTTP_PUT                    "PUT"
#define HTTP_DELETE                 "DELETE"


/*********************************************
* HTTP Content-Type String
*********************************************/
#define HTTP_CTYPE_MULTIPART_FORM   "multipart/form-data"
#define HTTP_CTYPE_APP_HTTP_FORM    "Application/x-www-form-urlencoded"
#define HTTP_CTYPE_APP_JS           "Application/javascript"
#define HTTP_CTYPE_APP_JSON         "Application/json"
#define HTTP_CTYPE_APP_XML          "Application/xml"
#define HTTP_CTYPE_TEXT_PLAIN       "text/plain"
#define HTTP_CTYPE_TEXT_HTML        "text/html"
#define HTTP_CTYPE_TEXT_CSS         "text/css"
#define HTTP_CTYPE_TEXT_JS          "text/javascript"
#define HTTP_CTYPE_TEXT_XML         "text/xml"


/*********************************************
* HTTP Simple Return Value
*********************************************/
// Return value
#define HTTPC_FAILED                0
#define HTTPC_SUCCESS               1
#define HTTPC_CONNECTED             2
// Return value: boolean type
#define HTTPC_FALSE                 0
#define HTTPC_TRUE                  1


/*********************************************
* HTTP Requset Structure Initializer
*********************************************/
#define HttpRequest_multipart_post_initializer {(uint8_t *)HTTP_POST, NULL, NULL, (uint8_t *)HTTP_CTYPE_MULTIPART_FORM, (uint8_t *)"keep-alive", 0}
#define HttpRequest_get_initializer            {(uint8_t *)HTTP_GET, NULL, NULL, NULL, (uint8_t *)"keep-alive", 0}


/*********************************************
* HTTP Boundary String for Multipart/form data
*********************************************/
#define formDataBoundary            "----WebKitFormBoundaryE8pT6qqUHgRhSDDC" // example boundary string for multipart form data


// HTTP client structure
typedef struct __HttpRequest {
	uint8_t * method;
	uint8_t * uri;
	uint8_t * host;
	uint8_t * content_type;
	uint8_t * connection;
	uint32_t content_length;
} __attribute__((packed)) HttpRequest;

// HTTP client status flags
extern uint8_t  httpc_isSockOpen;
extern uint8_t  httpc_isConnected;
extern uint16_t httpc_isReceived;

// extern: HTTP request structure
extern HttpRequest request;

/*********************************************
* HTTP Client Functions
*********************************************/
uint8_t  httpc_connection_handler(); // HTTP client socket handler - for main loop, implemented in polling

uint8_t  httpc_init(uint8_t sock, uint8_t * ip, uint16_t port, uint8_t * sbuf, uint8_t * rbuf); // HTTP client initialize
uint8_t  httpc_connect(); // HTTP client connect (after HTTP socket opened)
uint8_t  httpc_disconnect(void);

uint16_t httpc_add_customHeader_field(uint8_t * customHeader_buf, const char * name, const char * value); // Function for adding custom header fields (httpc_send_header() function only)
uint16_t httpc_send_header(HttpRequest * req, uint8_t * buf, uint8_t * customHeader_buf, uint16_t content_len); // Send the HTTP header only
uint16_t httpc_send_body(uint8_t * buf, uint16_t len); // Send the HTTP body only (have to send http request body after header sent)
uint16_t httpc_send(HttpRequest * req, uint8_t * buf, uint8_t * body, uint16_t content_len); // Send the HTTP header and body

uint16_t httpc_recv(uint8_t * buf, uint16_t len); // Receive the HTTP response header and body, User have to parse the received messages depending on needs


#endif /* HTTPCLIENT_H_ */
