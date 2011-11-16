#ifndef Restful_server_h
#define Restful_server_h

#include "WProgram.h"
#include "config_rest.h"
#include "message.h"
#include <Ethernet.h>
#include <SPI.h>


class RestServer {

	private:
		Message request;
		int process_state;
		
		char end_sequence[ELEMENT_DIV_LENGTH + 1];
		char div_chars[END_SEQ_LENGTH + 1];
		char current_service [NAME_LENGTH];

		long timeout_start_time;
		int timeout_period;

		boolean read_request(char);
		void parse_request ();
		void process();

		void send_response(Client);
		void send_response();
		void prepare_for_next_client();

		void read_services();
		int service_match(int, int, int);
		int state_match(int, int, int);

		int next_element(int);
		int check_for_state_msg(int);
		int check_start(int);
		int check_start_single(int);

	public:
		int services[SERVICE_TYPES];
		int service_get_state [GET_SERVICES_COUNT];
		int service_set_state [SET_SERVICES_COUNT];
		boolean service_get_requested [GET_SERVICES_COUNT];
		boolean service_set_requested [SET_SERVICES_COUNT];
		boolean service_set_updated [ELEMENT_DIV_LENGTH];

		RestServer();						// constructor
		void respond();						// notifies rest_server when ready to respond
		boolean handle_requests(Client); 	// reads request from Ethernet client
		boolean handle_response(Client); 	// sends response to Ethernet client
		boolean handle_requests(); 			// reads request from Serial client
		boolean handle_response(); 			// sends response to Serial client

};

#endif
