#include <iostream>
#include <cctype>
#include <string>
#include <stdexcept>
#include <vector>

bool is_only_letter(const std::string&);
bool is_only_digit(const std::string&);
bool is_digits_and_letters(const std::string&); // лишняя ( тк это просто две предыдушие взывать вместе)
std::string reverse_word(const std::string&);
std::string transform_word(const std::string&);
std::string process_string(const std::string&);

int main()
{
	try
	{
		std::string str;
		std::cout << "Enter your string: ";
		std::getline(std::cin, str);
		std::cout << '\n';
		std::string result = process_string(str);
		std::cout << "Result: " << result;
	}
	catch (const std::exception& error) // нельзя так писать, нужно отдельный класс ошибок делать
	{
		std::cerr << error.what();
	}
	return 0;
}

bool is_only_digit(const std::string& word)
{
	for (char symbol : word)
	{
		if (!isdigit(static_cast<unsigned char>(symbol)))
			return false;
	}
	return true;
}

bool is_only_letter(const std::string& word)
{
	for (char symbol : word)
	{
		if (!isalpha(static_cast<unsigned char>(symbol)))
			return false;
	}
	return true;
}

bool is_digits_and_letters(const std::string& word)
{
	bool has_digit{ false };
	bool has_letter{ false };
	for (char symbol : word)
	{
		if (isdigit(static_cast<unsigned char>(symbol)))
			has_digit = true;
		else
			if (isalpha(static_cast<unsigned char>(symbol)))
		    has_letter = true;
	}
	return (has_digit && has_letter);
}

std::string reverse_word(const std::string& word)
{
	return std::string(word.rbegin(), word.rend());
}

std::string transform_word(const std::string& word)
{
	if (is_only_digit(word) || word.size() < 7)
	{
		std::string result = "";
		result = reverse_word(word); // я бы это перенёс в объявление хз зач тебе сначала пустую строку создаавать
		return result;
	}
	else
		if (is_only_letter(word))
		{
			std::string result = "";
			for (char c : word)
			{
				result += std::tolower(static_cast<unsigned char>(c));
			}
			return result;
		}
		else
			if (is_digits_and_letters(word))
			{
				std::string result = "";
				for (char symbol : word)
				{
					result += std::toupper(static_cast<unsigned char>(symbol));
				}
				return result;
			}
			else
				throw std::invalid_argument("It is impossible to process the word."); // вот нужно ее ловить в кэтч , а не ексепшн
}

std::string process_string(const std::string& string)
{
	std::vector<std::string> words;
	std::string word;
	for (char symbol : string)
	{
		if (std::isalnum(symbol))
		{
			word.push_back(symbol);
		}
		else
			if (!word.empty())
			{
				words.push_back(word);
				word.clear();
			}
	}
	if (!word.empty())
	{
		words.push_back(word);
	}
	if (words.empty())
	{
		throw std::invalid_argument("String don't have words for processing.");
	}
	std::string output;
	for (const auto& word : words)
	{
		std::string current_word = transform_word(word);
		output += current_word;
		if (!output.empty()) // мне кажется это лишняя проверка, типо у тебя и так уже не пустая строка, тк ты в нее добавила чтото
		{
			output.push_back(' '); // АХАХАХХАХХАХАХХ пуш бэк в строку, это очень смшено
		}
	}
	return output;
}

