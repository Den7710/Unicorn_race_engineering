#include "integer.h"

#define num_of_response_mobs 2
#define data_buffer_num 2 

extern U8 response_buffer[num_of_response_mobs][8];
extern st_cmd_t response_msg[num_of_response_mobs];

extern U8 databuffer[data_buffer_num][8];
extern U8 bufferindex;

extern U8 tx_remote_buffer[8];
extern st_cmd_t tx_remote_msg;

extern U8 tx_buffer[8];
extern st_cmd_t tx_std_msg;

void init_can_data_mobs(void);
void can_data_mob_setup(U8 mob_num);

/* Funktion til at sende en besked via CAN */
//BOOL can_send_standart_data(dataPackage *, U8 *buf);

void can_send(U8 msg_id, U8 msg, U8 data_length);

void can_send_ny(U8 msg_id, void* msg, U8 data_length);

void can_send_test(U8 msg_id, void* msg, U8 data_length);
