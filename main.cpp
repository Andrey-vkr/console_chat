#include <iostream>
#include "Chat.h"


int main()
{
	setlocale(LC_ALL, "");

	Chat chat;

	chat.begin();

	while (chat.ChatWork())
	{
		chat.RegistrationShow();

		while (chat.getActualUser())
		{
			chat.MessagShow();
		}
	}
	return 0;
}



