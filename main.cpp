/*
this is just a demo project to learn c++, it's basically a shift encryption with a rolling key,
generated from a random seed. There are only 255 possible keys so the keyspace is extremly low
and thus the algorithm being based on rand() and srand(), one could probably predict upcomming
key values or the seed key when knowing some partial plaintext. Do not use this in production.
*/

#include <iostream>
#include <vector>
#include <string>


int py_mod(int a, int b)
//modulo like in python3
{
	if (a > 0) {
		return a % b;
	}
	else {
		return (a+b) % b;
	}
}

std::string shift_cipher_rotating(std::string &input, int key,char mode) {
	srand(key);
	std::string out = "";
	int newval = 0;

	for (unsigned char element : input) {
		int tmp_key = rand() % 255;


		if (mode == 'e') {
			newval = py_mod(int(element) + tmp_key,255);
		}
		else if (mode == 'd') {
			newval = py_mod(int(element) - tmp_key, 255);
		}
		
		out.push_back(unsigned char(newval));
	}
	return out;
}

int main()
{
	//todo: safe handling of input
	std::string user_input;
	while (true) {

		std::cout << ">";
		std::getline(std::cin, user_input);

		if (user_input == "enc") {
			
			std::string message;
			int enckey;

			std::cout << "enter your message:";

			std::getline(std::cin, message);

			std::cout << "enter your key:";

			std::cin >> enckey;

			if (!enckey) {
				std::cerr << "please enter an integer!" << std::endl;
			}
			else {
				auto out = shift_cipher_rotating(message, enckey, 'e');
				std::cout << "Your encrypted message:" << out << std::endl;
			}
			

		}

		else if (user_input == "dec") {
			std::string message;
			int enckey;

			std::cout << "enter your encrypted message:";

			std::getline(std::cin, message);

			std::cout << "enter your key:";

			std::cin >> enckey;

			if (!enckey) {
				std::cerr << "please enter an integer!" << std::endl;
			}
			else {
				auto out = shift_cipher_rotating(message, enckey, 'd');
				std::cout << "Your decrypted message:" << out << std::endl;
			}
		}
	}

}
