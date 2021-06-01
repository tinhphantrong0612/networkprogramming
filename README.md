# Design of network
## The response
| Code | ID | Length | Payload|
|---|---|---|---|
|2 bytes|4 bytes |4 bytes| max 2048 bytes|


## CODE
01: lOGIN
02: SIGNUP

## The login
01 | nuLL | strlen(data) |<username> <password>
02 | nuLL | strlen(data) |<username> <password>
