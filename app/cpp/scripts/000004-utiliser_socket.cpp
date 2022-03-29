//===============================================
// utiliser_socket
//===============================================

// envoi big data
unsigned int len = vect.size();
iResult = send( ConnectSocket, &len, sizeof(len), 0 ); // Sending The Length
iResult = send( ConnectSocket, &vect[0], vect.size(), 0 ); // Sending The File

