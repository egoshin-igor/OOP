#include "stdafx.h"

using namespace std;

const wstring EXIT_CODE = L"...";
const wchar_t  DELIMETR = L':';

multimap<wstring, wstring> GetDictionarymultimap(wifstream& dictionaryFile);
void AddNewWords(wofstream& dictionaryFile, multimap<wstring, wstring>& newWordsmultimap);
wstring WstringLower(wstring& wstr);
bool PrintTransatedWords(multimap<wstring, wstring>& words, const wstring& word);

int main(int argc, char* argv[])
{
	wcout.imbue(locale("rus_rus.866"));
	wcin.imbue(locale("rus_rus.866"));
	if (argc != 2)
	{
		wcout << L"Dictionary file is not specified in params\n";
		return 1;
	}
	wifstream dictionaryFile(argv[1]);
	dictionaryFile.imbue(std::locale(""));
	multimap<wstring, wstring> dictionary;
	multimap<wstring, wstring> newWordsmultimap;
	dictionary = GetDictionarymultimap(dictionaryFile);
	wstring word;
	wstring translatedWord;
	bool exit = false;
	bool newWordsAdded = false;
	while (!exit)
	{
		exit = getline(wcin, word) ? false : true;
		wstring lowerWord = WstringLower(word);
		
		if (lowerWord == EXIT_CODE)
		{
			exit = true;
			if (newWordsAdded)
			{
				wcout << L"В словарь были внесены изменения. Введите английские Y или y для сохранения перед выходом.\n";
				getline(wcin, word);
				if (word == L"y" || word == L"Y")
				{
					wofstream dictionaryFile(argv[1], ios::app);
					dictionaryFile.imbue(std::locale(""));
					AddNewWords(dictionaryFile, newWordsmultimap);
					wcout << L"Изменения сохранены. До свидания.";
				}
			}
		}
		else
		{
			if(!PrintTransatedWords(dictionary, lowerWord))
			{
				wcout << L"Неизвестное слово " << word << L". Введите перевод или пустую строку для отказа.\n";
				getline(wcin, translatedWord);
				if (translatedWord != L"")
				{
					newWordsAdded = true;
					newWordsmultimap.insert(pair<wstring, wstring>(lowerWord, translatedWord));
					dictionary.insert(pair<wstring, wstring>(lowerWord, translatedWord));
					dictionary.insert(pair<wstring, wstring>(translatedWord,lowerWord));
					wcout << L"Слово “" << word << L"” сохранено в словаре как “" << translatedWord << L"”.\n";
				}
				else
				{
					wcout << L"Слово “" << word << L"” проигнорировано.\n";
				}
			}
		}
	}
    return 0;
}

wstring WstringLower(wstring& wstr)
{
	wstring tempString = L"";
	for (size_t i = 0; i < wstr.size(); ++i)
	{
		tempString += towlower(wstr[i]);
	}
	return tempString;
}

multimap<wstring, wstring> GetDictionarymultimap(wifstream& dictionaryFile)
{
	wstring words;
	wstring translatedWord;
	multimap<wstring, wstring> dictionary;
	if (dictionaryFile.is_open())
	{
		while (getline(dictionaryFile, words))
		{
			size_t delimetrPos = words.find(DELIMETR);
			dictionary.insert(pair<wstring, wstring>(L"" + words.substr(0, delimetrPos), words.substr(delimetrPos + 1)));
		}
	}
	return dictionary;
}

void AddNewWords(wofstream& dictionaryFile, multimap<wstring, wstring>& newWordsmultimap)
{
	for (auto& result : newWordsmultimap)
	{
		dictionaryFile << result.first << L":" << result.second << L'\n';
		dictionaryFile << result.second << L":" << result.first << L'\n';
	}
}

bool PrintTransatedWords(multimap<wstring, wstring>& words, const wstring& word)
{
	bool isPrinted = false;
	auto wordIt = words.find(word);
	for (wordIt; wordIt != words.end(); ++wordIt)
	{
		isPrinted = true;
		wcout << L"" << wordIt->second;
		if ((++wordIt)->first == word)
		{
			--wordIt;
			wcout << L", ";
		}
		else
		{
			wcout << L'\n';
			break;
		}
	}
	return isPrinted;
}