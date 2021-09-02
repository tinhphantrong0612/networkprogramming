#pragma once

#include "stream.h"
#include "qmessagebox.h"


/* Use to store user info
   * @param	username    
   * @param state  USER_NONAUTH , USER_AUTH, USER_WATING, USER_INGAME
*/
class User {
public:
    char username[USERNAME_LEN + 1];
    int state;

    User();
    
    /* Send username and password to login to server
        * @param	socket		[IN]	Socket to communicate to server
        * @param	username	[IN]	username info
        * @param	password	[IN]	password
        * @return	NULL
    */
    void login_request(Socket& socket, char* username, char* password);
    
    /* Send username and password to signup to server
        * @param	socket		[IN]	Socket to communicate to server
        * @param	username	[IN]	username info
        * @param	password1	[IN]	origin password
        * @param	password2	[IN]	confirm password
        * @return	NULL
    */
    void signup_request(Socket& socket, char* username, char* password1, char* password2);
    
    /* Send logout request to server
        * @param	socket		[IN]	Socket to communicate to server
        * @return	NULL
    */
    void logout_request(Socket& socket);

    /* Attract login info from server
        * @param	payload		[IN]	Playload from server
        * @return	NULL
    */
    void login_response(char* payload);
    
    /* Attract signup info from server
        * @param	payload		[IN]	Playload from server
        * @return	NULL
    */
    void signup_response(char* payload);
    
    /* Attract logout info from server
        * @param	payload		[IN]	Playload from server
        * @return	NULL
    */
    void logout_response(char* payload);

    ~User();
};

