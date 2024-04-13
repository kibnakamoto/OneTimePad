 /* Copyright (C) 2022 Taha Canturk                                         
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <https://www.gnu.org/licenses/>.
  */

#include <iostream>
#include <stdint.h>
#include <random>
#include <memory>
#include <string.h>
#include <iomanip>
#include <sstream>
#include <array>
#include <vector>
#include <set>
#include <iterator>
#include <thread>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <filesystem>
#include <signal.h>
#include <sys/sysinfo.h>

/* Comment if extra elimination is wanted
 * there is an extra elimination process defined in around line 630, this elimination process is optional,
 * turn it on if you have too much data to process to limit the amount of words generated.
 * It basically checks if the starting letter of the word is one of the top 10 most common first letters
 * according to an oxford study.
 */
#define EXTRA_ELIMINATION

#if	 __cplusplus <= 201703L
	#error "C++20 required"
#endif /* __cplusplus <= 201703L */

#if !(defined(__unix__) || defined(__linux__) || defined(__MACH__))
	#error "!defined(__unix__) || !defined(__linux__) || !defined(__MACH__): program doesn't support other OSs"
#elif defined(_WIN32)
#error "specifically NOT designed for windows, use linux or unix or darwin(MAC OS) instead"
#endif /* if OS == unix or linux or mac os */


// raise when integer too large
class OneTimePadError : public std::runtime_error {
	public: explicit OneTimePadError(const char *str) : std::runtime_error(str) {}
};
	
bool nofill = 0;

// required libraries: jq

// global constants
// format of commonly used strings
const std::string open_sq_bracket = "\033[1;38;2;158;0;0m[\033[0m";
const std::string closed_sq_bracket = "\033[1;38;2;158;0;0m]\033[0m ";
const std::string closed_curly_bracket = "\x1b[1;38;2;183;180;188m}\x1b[0m";
const std::string open_curly_bracket = "\x1b[1;38;2;183;180;188m{\x1b[0m";
const std::string white_colon = "\033[1;37;5m:\033[0m ";
const std::string white_comma = "\x1b[1;38;2;183;180;188m,\x1b[0m ";
bool catched_sigint = 0;

std::shared_ptr<uint8_t> gen_priv_key(uint32_t n=16)
{
	// generate n byte private key
    std::shared_ptr<uint8_t> key(new uint8_t[n]);
    std::random_device randDev;
    std::mt19937 generator(randDev() ^ time(NULL));
    std::uniform_int_distribution<uint8_t> distr;
    for(uint32_t c=0;c<n;c++) key.get()[c] = distr(generator);
	return key;
}

// handle termination signals
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
inline void handler(sig_atomic_t sig) { catched_sigint = 1; }
#pragma GCC diagnostic pop

std::string hex(std::string inp)
{
	std::stringstream ss;
	for(unsigned int i=0;i<inp.length();i++) ss << std::hex << std::setfill('0') << std::setw(2) << (uint8_t)inp[i]+0;
	return ss.str();
}

// one time pad encryption scheme
template<typename T> 
std::string one_time_pad(std::string msg, T key, uint32_t len)
{
	std::string ciphertext = "";
	if constexpr(std::is_same<T, std::shared_ptr<uint8_t>>::value) {
		for(uint32_t i=0;i<len;i++) {
			ciphertext += msg[i] ^ key.get()[i];
		}
	} else {
		for(uint32_t i=0;i<len;i++) {
			ciphertext += msg[i] ^ key[i];
		}
	}
	return ciphertext;
}

// hex to ascii equivilent character
uint8_t chr(std::string dat)
{
	uint8_t uint8;
	std::stringstream ss;
	ss << dat;
	ss >> uint8;
	return uint8;
}

const std::string words[300] = {
	"you", "just", "is", "word", "sentence", "live", "add", "when", "water", "very", "away", "in",
	"such", "need", "one", "am", "open", "day", "idea", "boy", "follow", "important", "near",
	"first", "back", "along", "would", "far", "us", "but", "because", "how", "more", "together",
	"high", "here", "must", "eye", "any", "take", "around", "made", "part", "left", "year",
	"four", "night", "other", "story", "study", "head", "down", "man", "next", "from", "different",
	"men", "letter", "list", "side", "off", "had", "were", "can", "said", "use", "make", "it\'s", "cut",
	"Indian", "sound", "come", "earth", "stop", "all", "both", "an", "still", "every", "he",
	"mountain", "where", "face", "does", "again", "people", "your", "we", "have", "so", "been",
	"little", "light", "house", "and", "will", "many", "say", "has", "right", "put", "big", "do",
	"too", "land", "answer", "let", "their", "by", "name", "this", "out", "what", "learn",
	"America", "each", "song", "of", "place", "his", "into", "state", "her", "about", "young",
	"farm", "hard", "only", "watch", "work", "book", "try", "them", "even", "help", "me", "him",
	"know", "to", "most", "under", "always", "did", "write", "school", "city", "read", "leave",
	"sea", "animal", "close", "number", "long", "white", "great", "came", "large", "call", "ask",
	"went", "walk", "way", "give", "picture", "father", "my", "if", "not", "now", "mile", "look",
	"on", "which", "home", "river", "often", "two", "new", "over", "being", "before", "thought",
	"with", "seem", "family", "show", "well", "between", "old", "begin", "these", "see", "saw",
	"above", "think", "go", "its", "hear", "feet", "move", "find", "line", "found", "don\'t",
	"until", "thing", "grow", "hand", "be", "there", "below", "later", "soon", "for", "some",
	"talk", "change", "same", "who", "end", "got", "no", "they", "turn", "own", "paper", "are",
	"page", "food", "good", "really", "our", "should", "plant", "mean", "never", "than", "she",
	"also", "might", "up", "life", "small", "without", "sometimes", "example", "start", "enough",
	"play", "spell", "could", "or", "time", "something", "like", "tell", "those", "eat", "why",
	"began", "kind", "three", "it", "air", "tree", "world", "then", "get", "mother", "set",
	"miss", "once", "I", "while", "may", "last", "was", "keep", "as", "run", "took", "carry",
	"almost", "car", "another", "children", "group", "want", "few", "point", "much", "through",
	"that", "after", "country", "second", "girl", "at", "non", "test"
};

// most common starting letters according to oxford mathcenter
const char starting_letters[10] = {'t', 'a', 'i', 's', 'o', 'c', 'm', 'f', 'p', 'w'};

// the first most common 42 bigram values found by cryptanalytic frequency analysis
const std::string bigram[42] = {"th", "he", "in", "er", "an", "re", "on", "at", "en", "nd", "ti",
								"es", "or", "te", "of", "ed", "is", "it", "al", "ar", "st", "to",
								"nt", "ng", "se", "ha", "as", "ou", "io", "le", "ve", "co", "me",
								"de", "hi", "ri", "ro", "ic", "ne", "ea", "ra", "ce"};

// the first most common 16 trigram values found by cryptanalytic frequency analysis
const std::string trigram[16] = {"the", "and", "tha", "ent", "ing", "ion", "tio", "for", "nde",
								 "has", "nce", "edt", "tis", "oft", "sth", "men"};

// algorithm to try all trigrams and bigrams listed above to crack ciphertext
std::string *try_all(std::string msg, std::string val)
{
	unsigned int len = msg.length()-val.length()+1;
	std::string *tries = new std::string[len];
	for(unsigned int i=0;i<len;i++) {
		tries[i] = "";
		for(unsigned int j=0;j<val.length();j++) {
			tries[i] += msg[i+j] ^ val[j];
		}
	}
	return tries;
}

// an algorithm to find all the same elements and add them to another vector
std::pair<std::vector<std::array<std::string,2>>, std::vector<uint32_t>> find_all(std::vector<uint32_t>
																				 vec,std::vector<
																				 std::array<
																				 std::string,2>> 
																				 strv, uint32_t elem)
{
	std::vector<std::array<std::string,2>> ret;
	std::vector<uint32_t> nums;
	
	for(uint32_t i=0;i<vec.size();i++) {
		if(vec[i] == elem) {
			ret.push_back(strv[i]);
			nums.push_back(vec[i]);
			
		}
	}
	return {ret, nums};
}

// find the amount of specific unieqe values in vector
uint32_t *unieqe_len(std::vector<uint32_t> vec, uint32_t &len) {
	std::set<uint32_t> set;
	for(auto i : vec) set.insert(i);
	
	len = set.size();
	uint32_t *lens = new uint32_t[len];
	for(uint32_t i=0;i<len;i++) {
		lens[i] = 0;
	}
	
	uint32_t i=0;
	for(auto s : set) {
		for(auto j : vec) {
			if(j == s) lens[i]++;
		}
		i++;
	}
	return lens;
}

// define custom run-time warnings
void inline warning(const std::string msg) {
    std::cout << std::endl << "\033[95;1;5mwarning: \033[0m\033[95;23m" << msg << "\033[0m" << std::endl;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void try_combinations(uint32_t *sizes, uint32_t sizes_len, uint32_t &thread_num, std::vector<std::array<std::string, 2>> &ord_w,
					  std::vector<uint32_t> &ord_w_ind, uint32_t len, std::string m1m2)
{
	std::ofstream file("py" + std::to_string(thread_num) + ".py");
	file << "import sys"
	     << "\nfrom random import randrange"
		 << "\ndef onetimepad(x:str,y:str) -> str:"
		 << "\n    ret = \"\"\n"
		 << "\n    for i in range(len(x)):\n"
	     << "\n        ret += chr(ord(x[i]) ^ ord(y[i]))"
	     << "\n    return ret\n"
	     << "\ndef hx(x):"
	     << "\n    ret = []"
	     << "\n    for i in x:"
	     << "\n        ret.append(hex(ord(i))[2:].zfill(2))"
	     << "\n    return ret\n";
	file << "\nm1m2 = \"" << hex(m1m2) << "\""
	     << "\nm1m2 = [m1m2[j:j+2] for j in range(0, len(m1m2), 2)]";
	file << "\nord_w0 = [";
	for(uint32_t i=0;i<ord_w.size();i++) {
		file << "\""  << ord_w[i][0] << "\"";
		if(i != ord_w.size()-1) file << ", ";
	}
	file << "]\nord_w1 = [";
	for(uint32_t i=0;i<ord_w.size();i++) {
		file << "\""  << ord_w[i][1] << "\"";
		if(i != ord_w.size()-1) file << ", ";
	}
	file << "]\nindexes = [";
	for(uint32_t i=0;i<ord_w_ind.size();i++) {
		if(ord_w_ind[i] != 0){
			file << ord_w_ind[i];
			if(i != ord_w_ind.size()-1) file << ", ";
		}
	}
	file << "]\nf = open(\"out/output" << thread_num << ".txt\", \"w\")\n";
	std::string tabs = "    ";
	uint32_t num = sizes[0];
                    
	// write the nested loops
	for(uint32_t i=1;i<sizes_len;i++) {
		std::string parameters = "";
		for(uint32_t j=1;j<i;j++) {
			parameters += "i" + std::to_string(j-1);
			if(j != sizes_len-1) parameters += ", "; 
		}
		file << "\ndef process" << i-1 << "(" << parameters << "):";

		if(i == 1) {
    		file << "\n" << tabs << "sys.stdout.write(f\"\\r\")"
         		 << "\n" << tabs << "sys.stdout.write(\"\x1b[4;2;1;38;2;7;224;21m%-100s\t\t\033[1;38;2;7;224;21m%d%%\033[0m\" % (\"\", 0))";
		}
		file << "\n" << tabs << "for i" << i-1 << " in range(" << num << ", " << num+sizes[i] << "):\n";
		if(i == sizes_len-1) {
			tabs += tabs;
    		file << "\n" << tabs << "string = list(\" \"*" << len << ")"
    			 << "\n" << tabs << "string2 = list(\" \"*" << len << ")"
    		     << "\n" << tabs << "for i in range(len(ord_w0[" << thread_num << "])):"
    		     << "\n" << tabs << "    string[i] = ord_w0[" << thread_num << "][i]"
    		     << "\n" << tabs << "    string2[i] = ord_w1[" << thread_num << "][i]"
    		     << "\n" << tabs << "ind = list(set(indexes))[0]"
    		     << "\n" << tabs << "for i in range(len(ord_w0[i0])):"
    		     << "\n" << tabs << "    if string[ind+i] == \' \':"
    		     << "\n" << tabs << "        string[ind+i] = ord_w0[i0][i]"
    		     << "\n" << tabs << "    if string2[ind+i] == \' \':"
    		     << "\n" << tabs << "        string2[ind+i] = ord_w1[i0][i]";
			for(uint32_t i=1;i<sizes_len-1;i++) {
    		    file << "\n" << tabs << "ind = list(set(indexes))[" << i << "]"
    		         << "\n" << tabs << "for i in range(len(ord_w0[i" << i <<"])):"
    		         << "\n" << tabs << "    if string[ind+i] == \' \':"
    		         << "\n" << tabs << "        string[ind+i] = ord_w0[i" << i <<"][i]"
    		         << "\n" << tabs << "    if string2[ind+i] == \' \':"
    		         << "\n" << tabs << "        string2[ind+i] = ord_w1[i" << i <<"][i]";
			}
			if (not nofill) {
				file << "\n" << tabs << "for ind in range(" << len << "):"
				     << "\n" << tabs << "    number = 32"  // 32 is ' '
				     << "\n" << tabs << "    tried = False"  // 32 is ' '
				     << "\n" << tabs << "    while hx(onetimepad(string, string2))[ind] != m1m2[ind]:" // if index doesn't match
				     << "\n" << tabs << "        for i in range(97, 122):" // for letters only, use range(97,122), except this can result in an endless loop
				     << "\n" << tabs << "            if number ^ i == int(m1m2[ind], 16):"; // generate index from ascii encoding 65 to 123 (common letters and symbols)
    			std::random_device randDev;
    			std::mt19937 generator(randDev() ^ time(NULL));
    			std::uniform_int_distribution<uint8_t> distr;
				if(distr(generator)%2) {
				    file << "\n" << tabs << "                string[ind] = chr(number)"
				         << "\n" << tabs << "                string2[ind] = chr(i)"
    				        "\n" << tabs << "                tried = True"
				         << "\n" << tabs << "                break";
				} else {
    				file << "\n" << tabs << "                string2[ind] = chr(number)"
    				        "\n" << tabs << "                string[ind] = chr(i)"
    				        "\n" << tabs << "                tried = True"
    				        "\n" << tabs << "                break";
				}
				file << "\n" << tabs << "        if not tried:"
				     << "\n" << tabs << "            number = randrange(48,129)";
			}

			file << "\n" << tabs << "strings = \"\\\"\" + \'\'.join(i for i in string) + \"\\\" : \\\"\" + \'\'.join(i for i in string2) + \"\\\"\""
    		     << "\n" << tabs << "f.write(strings + \"\\n\")";
		} else {
			file << tabs << "    process" << i << "(" << parameters << "i" << i-1 << ")";
			if(i == 1) {
		    	file << "\n" << tabs << "    progress=(i0-" << sizes[0]-1 << ")*100//(" << sizes[1] << ")"
		    	     << "\n" << tabs << "    progress_bar=\"_\"*progress"
		    	     << "\n" << tabs << "    sys.stdout.write(f\"\\r\")"
		    	     << "\n" << tabs << "    sys.stdout.write(\"\x1b[4;2;1;38;2;7;224;21m%-100s\t\t\033[1;38;2;7;224;21m%d%%\033[0m\" % (progress_bar, progress))";
			}
		}
		num += sizes[i];
	}
	file << "\nprocess0()\n";
	file << "\nf.close()\n";
	file.close();
	system((std::string("mv py") + std::to_string(thread_num) + std::string(".py out/")).c_str()); // move to out folder
	system((std::string("python3 out/py") + std::to_string(thread_num) + std::string(".py")).c_str());
}
#pragma GCC diagnostic pop
		
// function for calculating possible sentences using multi-threading, this function is for single-thread
void init_pos_sent(std::vector<std::array<std::string, 2>> &ord_w, uint32_t *sizes, uint32_t sizes_len,
				   uint32_t len, uint32_t thr_num, std::vector<uint32_t> &ord_w_ind, std::string m1m2)
{
	struct sysinfo mem_info;
	sysinfo (&mem_info);
	uint64_t ram_available;
	ram_available = mem_info.freeswap+mem_info.freeram;

	std::cout << "\nRam Available:\t" << ram_available << "B \t\t\ton thread " << thr_num << ".\n";
	try_combinations(sizes, sizes_len, thr_num, ord_w, ord_w_ind, len, m1m2);
	std::cout << "\nfinished thread " << thr_num;
}

void print_ord_w(std::vector<std::array<std::string, 2>> ord_w, std::vector<uint32_t> ord_w_ind)
{
	std::cout << std::endl << "\033[32;1mORD_W:\t\033[0m";
	for(uint32_t i=0;i<ord_w.size();i++) {
		std::cout << "\x1b[38;2;16;124;224m(\x1b[0mi:\x1b[38;2;16;124;224m" << i << "\x1b[0m - " 
				  << open_sq_bracket << "\x1b[37;23m" << ord_w_ind[i] << "\x1b[0m" << white_colon
				  << open_curly_bracket << "\x1b[3m" << ord_w[i][0] << "\x1b[0m" << white_comma
				  << "\033[3m" << ord_w[i][1] << "\033[0m" << closed_curly_bracket
				  << closed_sq_bracket << "\b\x1b[38;2;16;124;224m)\x1b[0m  ";
	}
	std::cout << std::endl << "\x1b[31mord_w count:\t\x1b[0m\033[37;1m" << ord_w.size() << "\033[0m" << std::endl;
}

int main(int argc, char *argv[])
{
	//const std::string m1 = "thetestvector";//"thetestvector";
	//const std::string m2 = "non-sensecode";//"non-sensecode";
	std::string m1;
	std::string m2;
	std::string mode;
	std::shared_ptr<uint8_t> key;
	std::string ciph1;
	std::string ciph2;
	std::string eq;
	uint32_t _len;
	system("python3 dotart.py");
	std::cout << "\nEnter (\x1b[5;1;38;2;16;255;22mC\x1b[0m)iphertext or (\033[5;1;38;2;255;16;22mP\033[0m)laintext of two sentences\ninput:\t";
	std::getline(std::cin, mode);
	if(mode[0] == 'p' or mode[0] == 'P') {
		std::string __k;
		std::cout << "\n\x1b[38;2;16;124;224mEnter two plaintext sentences of the same length\x1b[0m\n\033[1;38;2;255;16;22minput sentence one:\033[0m\t";
		std::getline(std::cin, m1);
		std::cout << "\n\x1b[12;1;38;2;85;255;85minput sentence two:\x1b[0m\t";
		std::getline(std::cin, m2);
		std::cout << "\n\x1b[38;2;16;124;224mInput key as hexadecimal, press enter to generate one, key has to be the same length as the message\ninput:\x1b[0m\t";
		std::getline(std::cin, __k);
		_len = m1.length(); // 13
		if(__k == "") {
			key = gen_priv_key(_len);
		} else {
			key = std::shared_ptr<uint8_t>(new uint8_t[_len]);
			for (uint32_t i=0;i<__k.length();i+=2)
    			key.get()[i/2] = (uint8_t)strtol(__k.substr(i, 2).c_str(), NULL, 16);
		}
		std::cout << std::endl << "M1:\t" << hex(m1) << std::endl << "M2:\t" << hex(m2) << std::endl << "KEY:\t";

		// encrypt messages using one time pad
		ciph1 = one_time_pad<std::shared_ptr<uint8_t>>(m1, key, _len);
		ciph2 = one_time_pad<std::shared_ptr<uint8_t>>(m2, key, _len);
		eq = one_time_pad<std::string>(m1,m2,_len);
		for(uint32_t i=0;i<_len;i++) {
			std::cout << std::setfill('0') << std::setw(2) << std::hex << key.get()[i]+0;
		}
	} else { // two ciphertexts will be given (they both have to have been encryped using the same key)
		std::string _ciph1, _ciph2;
		std::cout << "\n\x1b[38;2;16;124;224mEnter two encrypted sentences of the same length (in hex)\x1b[0m\n\033[1;38;2;255;16;22minput ciphertext one:\033[0m\t";
		std::cin >> _ciph1;
		std::cout << "\n\x1b[12;1;38;2;85;255;85mInput ciphertext two:\x1b[0m\t";
		std::cin >> _ciph2;
		ciph1="";
		ciph2="";
		_len = !((_ciph1.length()/2)%2==0) ? _ciph1.length()/2 : _ciph1.length()/2+1; // if ciph1 len isn't a multiple of 2, add 1
		for (uint32_t i=0;i<_ciph1.length();i+=2)
   			ciph1 += (uint8_t)strtol(_ciph1.substr(i, 2).c_str(), NULL, 16);
		for (uint32_t i=0;i<_ciph2.length();i+=2)
    		ciph2 += (uint8_t)strtol(_ciph2.substr(i, 2).c_str(), NULL, 16);
		eq = one_time_pad<std::string>(ciph1, ciph2, _len);
	}
	const uint32_t len = _len; // 13
	
	std::string m1m2 = one_time_pad<std::string>(ciph1, ciph2, len);
	std::cout << std::endl << std::endl << "C1:\t" << hex(ciph1) << std::endl << "C2:\t" << hex(ciph2)
			  << std::endl << "M1M2:\t" << std::flush << hex(m1m2) << std::endl << "EQ (plaintexts xor'ed if available, else ciphertexts):\t"
			  << hex(eq) << std::endl;
	std::cout << "\nCIPHERTEXT SIZE:\t" << std::dec << m1m2.length() << std::endl;

	// map of values for starting index and possible n-gram
	std::vector<std::array<std::string, 2>> possible_bigrams;
	std::vector<uint32_t> possible_bigrams_ind;
	std::vector<std::array<std::string, 2>> possible_bigrams1;
	std::vector<uint32_t> possible_bigrams1_ind;
	std::vector<std::array<std::string, 2>> possible_trigrams;
	std::vector<uint32_t> possible_trigrams_ind;
	std::vector<std::array<std::string, 2>> possible_words;
	std::vector<uint32_t> possible_words_ind;

	const unsigned int bi_i = len-1;
	const constexpr unsigned int bi_len = sizeof(bigram)/sizeof(bigram[0]);
	const unsigned int tri_i = len-2;
	const constexpr unsigned int tri_len = sizeof(trigram)/sizeof(trigram[0]);
	const constexpr unsigned int word_len = std::size(words);

	if(m1m2.length() < 3) {
		std::cout << std::endl << "m1m2: \"" << m1m2 << "\"\t|\tlen: " << m1m2.length() << std::endl;
		throw OneTimePadError("ciphertexts are smaller than 3 bytes, no possible combinations");
	}

	// decrypt one of the messages using bigram
	for(unsigned int i=0;i<bi_len;i++) {
		// calculate first plaintext
		std::string *tries = try_all(m1m2, bigram[i]);
		std::cout << std::endl << "FOR STRING \"" << bigram[i] << "\" TRY1:\t\t";
		for(unsigned int j=0;j<bi_i;j++) std::cout << std::setfill('0') << std::setw(2)
												   << tries[j] << " ";

		// calculate second plaintext based on tries on calculating first plaintext
		// which can be anything
		std::cout << std::endl << "FOR STRING ^ABOVE^ TRY2:\t";
		for(unsigned int j=0;j<bi_i;j++) {
			bool valid_tries = false;
			// check if tries is a syllable in one of the 299 or so common words
			for(unsigned int k=0;k<word_len;k++) {
				valid_tries = words[k].find(tries[j]) != std::string::npos;
				if (valid_tries) break;
			}
			if (valid_tries) { // if one of the plaintexts are valid text, try the other plaintext
				std::string tmp = one_time_pad<std::string>(tries[j], m1m2.substr(j,2), 2);
				std::cout << std::setfill(' ') << std::setw(2) << tmp; // if tmp = bigram[i], it is correct

				// if tmp is a syllable in words, it is common and will be allegdly seen as
				// part of one of the plaintexts
				for(unsigned int k=0;k<word_len;k++) {
					size_t find = words[k].find(tmp);
					if(find != std::string::npos) {
						std::array<std::string, 2> temp_arr = {tries[j], tmp};
						possible_bigrams.push_back(temp_arr);
						possible_bigrams_ind.push_back(j);
						break;
					}
				}
			} else {
				std::cout << "  ";
			}
			std::cout << " ";
		}
		delete[] tries;
	}

	// decrypt one of the messages using trigram
	for(unsigned int i=0;i<tri_len;i++) {
		std::string *tries = try_all(m1m2, trigram[i]);
		std::cout << std::endl << "FOR STRING \"" << trigram[i] << "\" TRY1:\t\t";
		for(unsigned int j=0;j<tri_i;j++) std::cout << std::setfill('0') << std::setw(3)
													<< tries[j] << " ";
		
		// calculate second plaintext based on tries on calculating first plaintext which
		// can be anything
		std::cout << std::endl << "FOR STRING ^ABOVE^ TRY2:\t";
		for(unsigned int j=0;j<tri_i;j++) {
			bool valid_tries = false;
			for(unsigned int k=0;k<word_len;k++) {
				valid_tries = words[k].find(tries[j]) != std::string::npos;
				if (valid_tries) break;
			}
			if(valid_tries) {
				std::string tmp = one_time_pad<std::string>(tries[j], m1m2.substr(j,3), 3);
				std::cout << std::setfill('0') << std::setw(3) << tmp;
	
				// if tmp is in words, it is common and will be allegedly seen as part of the message
				for(unsigned int k=0;k<tri_len;k++) {
					size_t find = words[k].find(tmp);
					if(find != std::string::npos) {
						std::array<std::string, 2> temp_arr = {tries[j], tmp};
						possible_trigrams.push_back(temp_arr);
						possible_trigrams_ind.push_back(j);
						break;
					}
				}
			} else {
				std::cout << "   ";
			}
			std::cout << " ";
		}
		delete[] tries;
	}

	// try all the words in word list, combine all combinations to come up with something
	for(unsigned int i=0;i<word_len;i++) {
		if(m1m2.length() < words[i].length()) continue; // skip word if m1m2 length is smaller. To avoid error
		std::string *tries = try_all(m1m2, words[i]);

		// calculate length of indendation for TRY1 and TRY2:
		std::string indent1 = std::string(words[i].length() < 5 ? 5-words[i].length() : 0, ' '); // 5 is the length of word "ABOVE" in TRY2
		std::string indent2 = std::string(words[i].length() > 5 ? words[i].length()-5 : 0, ' ');

		std::cout << std::endl << "FOR STRING \"" << words[i] << "\"" << indent1 << " TRY1:\t";
		for(unsigned int j=0;j<len-words[i].length()+1;j++) std::cout << std::setfill(' ')
																	  << std::setw(words[i].length())
																	  << tries[j] << " ";

		// calculate second plaintext based on tries on calculating first plaintext, which can
		// be anything
		std::cout << std::endl << "FOR STRING ^ABOVE^" << indent2 << " TRY2:\t";
		for(unsigned int j=0;j<len-words[i].length()+1;j++) {
			bool valid_tries = false;
			for(unsigned int k=0;k<word_len;k++) {
				valid_tries = words[k].find(tries[j]) != std::string::npos;
				if (valid_tries) break;
			}
			if (valid_tries) {
				std::string tmp = one_time_pad<std::string>(tries[j], m1m2.substr(j,words[i].length()),
															words[i].length());
				std::cout << std::setfill(' ') << std::setw(words[i].length()) << tmp;
	
				// if tmp in words, it is common and will be allegedly seen as part of the message
				for(unsigned int k=0;k<word_len;k++) {
					if (tmp == words[k]) {
						std::array<std::string, 2> temp_arr = {tries[j], tmp};
						possible_words.push_back(temp_arr);
						possible_words_ind.push_back(j);
					}
				}
			} else {
				for(uint32_t k=0;k<words[i].length();k++) std::cout << " ";
			}
			std::cout << " ";
		}
		delete[] tries;
	}

	uint32_t index = 0;
	std::vector<std::array<std::string, 2>> ord_bigrams;
	std::vector<uint32_t> ord_bigrams_ind;

	uint32_t max = possible_bigrams_ind.size()==0 ? 0 : *max_element(possible_bigrams_ind.begin(), possible_bigrams_ind.end());
	// order possible_bigrams
	while(index <= max) {
		auto [ret, nums] = find_all(possible_bigrams_ind, possible_bigrams, index);
		for(uint32_t i=0;i<ret.size();i++) {
			ord_bigrams.push_back(ret[i]);
			ord_bigrams_ind.push_back(nums[i]);
		}
		index++;
	}
	possible_bigrams = ord_bigrams;
	possible_bigrams_ind = ord_bigrams_ind;

	std::vector<std::array<std::string, 2>> ord_trigrams;
	std::vector<uint32_t> ord_trigrams_ind;
	index = 0;
	max = possible_trigrams_ind.size()==0 ? 0 : *max_element(possible_trigrams_ind.begin(), possible_trigrams_ind.end());

	if(possible_trigrams.size() != 0) {
		// order possible_trigrams
		while(index <= max) {
			auto [ret, nums] = find_all(possible_trigrams_ind, possible_trigrams, index);
			for(uint32_t i=0;i<ret.size();i++) {
				ord_trigrams.push_back(ret[i]);
				ord_trigrams_ind.push_back(nums[i]);
			}
			index++;
		}
	}
	possible_trigrams = ord_trigrams;
	possible_trigrams_ind = ord_trigrams_ind;

	std::vector<std::array<std::string, 2>> ord_w;
	std::vector<uint32_t> ord_w_ind;
	max = possible_words_ind.size()==0 ? 0 : *max_element(possible_words_ind.begin(), possible_words_ind.end());
	index = 0;
	
	uint32_t sizes_len=0;
	uint32_t *sizes;
	if (possible_words_ind.size()!=0) {
		// order possible_words
		while(index <= max) {
			auto [ret, nums] = find_all(possible_words_ind, possible_words, index);
			for(uint32_t i=0;i<ret.size();i++) {
				ord_w.push_back(ret[i]);
				ord_w_ind.push_back(nums[i]);
			}
			index++;
		}
		

		// calculate the amount of every unieqe index
		sizes = unieqe_len(ord_w_ind, sizes_len);

		//////////////// EXTRA ELIMINITAION-PROCESSES TO SAVE MEMORY AND TIME ////////////////
#if defined(EXTRA_ELIMINATION) // extra elimination on
		// make sure the starting index is common
		for(uint32_t i=0;i<sizes[0];i++) {
			bool valid_start = 0;
			for(uint32_t j=0;j<10;j++) {
				valid_start |= ord_w[i][0][0] == starting_letters[j] or ord_w[i][1][0] == starting_letters[j];
			}
			if(!valid_start) {
				ord_w.erase(ord_w.begin()+i);
				ord_w_ind.erase(ord_w_ind.begin()+i);
			}
		}
#endif

		// calculate all possible bigrams on the 0th index
		std::vector<std::array<std::string, 2>> starting_bigrams;
		for(uint32_t i=0;i<possible_bigrams.size();i++) {
			if (possible_bigrams_ind[i] == 0) {
				starting_bigrams.push_back(possible_bigrams[i]);
			}
		}

		// make sure that the starting indexes of ord_w is equal to bigram, if it checks out, it is 
		// probably correct
		for(uint32_t i=0;i<sizes[0];i++) {
			bool found = 0;
			for(uint32_t j=0;j<starting_bigrams.size();j++) {
				found or_eq (ord_w[i][0].find(starting_bigrams[j][1]) not_eq std::string::npos) |
						 	(ord_w[i][1].find(starting_bigrams[j][0]) not_eq std::string::npos) |
							(ord_w[i][1].find(starting_bigrams[j][1]) not_eq std::string::npos) |
							(ord_w[i][0].find(starting_bigrams[j][0]) not_eq std::string::npos);
			}
			if(!found) {
				ord_w.erase(ord_w.begin()+i);
				ord_w_ind.erase(ord_w_ind.begin()+i);
			}
		}
		
		///////////////// PROBLEM WITH sizes[5] = sizes_till_n updated in UI is caused by how c command is defined later while 
		// print comes first.
		delete[] sizes;
		sizes = unieqe_len(ord_w_ind, sizes_len);

		// CLI for removing certain values based on how much they make sense to the user after
		// concatination of ord_w elements. This is mostly to decrease the amount of threads running
		// so that any device can run the code.
		// const bool args = argc == 2 and argv[1][0] != 48; // 48 = '0'
		bool args=0;
		
		if(argc > 1) {
			for(int i=1;i<argc;i++) {
				if(strcmp(argv[i],"1") == 0) args=1;
				if(strcmp(argv[i],"--no-fill") == 0) nofill=1;
			}
		}
		//exit(EXIT_FAILURE);
		while(args) {
			print_ord_w(ord_w, ord_w_ind);
			uint32_t v = 0;
			uint32_t sizes_index = 0;
			uint64_t sizes_till_n = sizes[0];
			while(v < ord_w.size()-sizes[sizes_len-1]+1) {
				std::array<std::string, 4> *comb = new std::array<std::string, 4>[ord_w.size()-1]; // 2 combinations per message (2 m1, 2 m2)=4
				while(true) {
					auto combinations = [&](uint32_t j)
					{
						// find 2 combinations per message:
						// uint8_t comb_len = ord_w[v][0].length() + ord_w[j][0].length() - ord_w_ind[j]+ord_w_ind[v]; // length of one combination
						uint8_t comb_len = ord_w[j][0].length() + ord_w_ind[j] - ord_w_ind[v]; // length of one combination
						char* combv0 = new char[comb_len];
						char* combv1 = new char[comb_len];
						char* combv2 = new char[comb_len];
						char* combv3 = new char[comb_len];
						memset(combv0, ' ', comb_len);
						memset(combv1, ' ', comb_len);
						memset(combv2, ' ', comb_len);
						memset(combv3, ' ', comb_len);

						// last overlaps first
						memcpy(combv0, ord_w[v][0].c_str(), ord_w[v][0].length());
						memcpy(combv3, ord_w[v][1].c_str(), ord_w[v][1].length());

						memcpy(&combv0[ord_w_ind[j]-ord_w_ind[v]], ord_w[j][0].c_str(), ord_w[j][0].length());
						memcpy(&combv3[ord_w_ind[j]-ord_w_ind[v]], ord_w[j][1].c_str(), ord_w[j][1].length());

						// first overlaps last
						memcpy(&combv1[ord_w_ind[j]-ord_w_ind[v]], ord_w[j][0].c_str(), ord_w[j][0].length());
						memcpy(&combv2[ord_w_ind[j]-ord_w_ind[v]], ord_w[j][1].c_str(), ord_w[j][1].length());

						memcpy(combv1, ord_w[v][0].c_str(), ord_w[v][0].length());
						memcpy(combv2, ord_w[v][1].c_str(), ord_w[v][1].length());

						comb[v][0] = std::string(combv0, comb_len); // m1
						comb[v][1] = std::string(combv1, comb_len); // m1
						comb[v][2] = std::string(combv2, comb_len); // m2
						comb[v][3] = std::string(combv3, comb_len); // m2

						delete[] combv0;
						delete[] combv1;
						delete[] combv2;
						delete[] combv3;
					};

					std::string input = "";
					std::cout << std::endl << "input index to remove or to see certain values:\t";
					signal(SIGINT, handler);
					if (catched_sigint) goto tried_quit;
					std::getline(std::cin, input);
					if(input.find("help") != std::string::npos) {
						system("jq . help.json"); // pretty print json
					} else if(input == "") {
						std::cout << "\b" << std::flush;
					} else if(input == "c") { // continue the loop, by increasing n and dependants of n
						if(v<ord_w.size()-sizes[sizes_len-1]) {
							// calculate sizes[i] for loop j for combinations
							if(v == sizes_till_n) {
								sizes_index++;
								sizes_till_n += sizes[sizes_index];
							}
						} else {
							std::cout << std::flush
									  << "\ncombinations iteration done. Type \"r\" to reset loop. Type \"exit\" to exit\n";
							delete[] comb;
							goto first_for_loop;
						}

						for(uint32_t j=sizes_till_n;j<sizes_till_n+sizes[sizes_index+1];j++) {
							std::string format = "\033[38;2;16;124;224";
							if(j%2 == 0) format += ";5m"; // print format for making every 2 values blink
							else format += "m";


							combinations(j);

							std::cout << "\n\x1b[38;2;16;124;224mcombination =\x1b[0m " << open_sq_bracket
									  << comb[v][0] << "\033[31;1m/\033[0m" << comb[v][1] 
									  << " \033[31;1m:\033[0m " << comb[v][2] << "\033[31;1m/\033[0m" <<  comb[v][3]
									  << "\t\x1b[37m-1:\x1b[0m" << format << v
									  << "\033[0m\t\x1b[37m-2:\x1b[0m\033[38;2;16;124;224m" << j
									  << "\033[0m" << closed_sq_bracket;
						}
						v++;
						goto first_for_loop;
					} else if(std::all_of(input.begin(),input.end(), [](char inp) {return isdigit(inp);})) {
						uint32_t digit = static_cast<uint32_t>(std::stoul(input));
						if(digit < ord_w.size()) {
							ord_w.erase(ord_w.begin()+digit);
							ord_w_ind.erase(ord_w_ind.begin()+digit);
							delete[] sizes;
							sizes = unieqe_len(ord_w_ind, sizes_len);
							sizes_index = 0;
							v = 0;
							sizes_till_n = sizes[0];

						} else {
							std::cout << std::endl << "input too large, has to be smaller than "
									  << ord_w.size();
						}
					} else if(input.starts_with("see")) {
						if(std::any_of(input.begin(),input.end(), [](char inp) {return inp == 'o';})) { // print ord_w
							print_ord_w(ord_w, ord_w_ind);
						} else if(std::any_of(input.begin(),input.end(), [](char inp) {return inp == 'l';})) { // print sizes
							delete[] sizes;
							sizes = unieqe_len(ord_w_ind, sizes_len);
							std::cout << "\nsizes:\t" << open_sq_bracket;
							for(uint32_t i=0;i<sizes_len;i++) {
								std::cout << sizes[i];
								if(i < sizes_len-1) {
									std::cout << ", ";
								}
							}
							std::cout << closed_sq_bracket << std::endl;
						} else if(std::any_of(input.begin(),input.end(), [](char inp) {return inp == 'n';})) { // print v
								std::cout << std::endl << "n:" << v << " - " << ord_w.size()-v
									<< " amount of iterations left, type \"c\" to continue loop"
										  << " and increment n, type \"r\" to reset n to 0 and re-loop";
						} else if(std::any_of(input.begin(), input.end(), [](char inp) {return inp == 'c';})) { // print comb
							delete[] sizes;
							sizes = unieqe_len(ord_w_ind, sizes_len);
							std::cout << std::endl << "\x1b[38;2;16;124;224mcombinations:\x1b[0m\t"
									  << open_curly_bracket << "\n";

							// re-calculate comb since ord_w might be updated
							for(uint32_t j=sizes_till_n;j<sizes_till_n+sizes[sizes_index+1];j++) {
								std::string format = "\033[38;2;16;124;224";
								if (j%2 == 0) format += ";5m"; // print format for making every 2 values blink
								else format += "m";

								// find 2 combinations per message:
								combinations(j);

								std::cout << "\n\t\x1b[38;2;16;124;224mcombination =\x1b[0m " << open_sq_bracket
										  << comb[v][0] << "\033[31;1m/\033[0m" << comb[v][1] 
										  << " \033[31;1m:\033[0m " << comb[v][2] << "\033[31;1m/\033[0m" <<  comb[v][3]
										  << "\t\x1b[37m-1:\x1b[0m" << format << v
										  << "\033[0m\t\x1b[37m-2:\x1b[0m\033[38;2;16;124;224m" << j
										  << "\033[0m" << closed_sq_bracket;
							}
							std::cout << std::endl << closed_curly_bracket;
						} else {
							std::stringstream ss;
						    ss << "\x1b[21;31;1merror\x1b[0m\033[31;1m:\033[m \033[9;1m" << input
							   << "\033[0m\033[1;38;2;128;0;0;5m:\033[0m invalid sub-command";
							std::cout << ss.str();
						}
					} else if(input == "q") {
						tried_quit:
						catched_sigint = 0;
						std::cout << "\n\x1b[1;38;2;255;16;22mare you sure you want to quit?\x1b[0m "
								  << "(\x1b[12;1;38;2;85;255;85my\x1b[0m/\033[1;31;13mn\033[0m) ";
						char verify;
						std::cin >> verify;
						if (verify == 'y') {
							std::cout << "\033[4A\x1b[4K\n\033[4D\033[2K";
							goto loop1;
						} else {
							std::cout << "\033[4A\x1b[4K\n\033[4D\033[2K";
						}
					} else if(input == "exit") {
						goto stop;
					} else if(input == "r") {
						v = 0;
						sizes_index=0;
						sizes_till_n = sizes[0];
					} else {
						system("jq . help.json"); // pretty print json
					}
				}

				first_for_loop:
					continue;
			}
			loop1:
				std::cout << "\033[31;1mexit?\033[0m (\033[5;38;2;16;255;22my\033[0m/\x1b[38;2;158;0;0;1mn\x1b[0m) ";
				char verify;
				std::cin >> verify;
				if (verify == 'y') {
					std::cout << "\x1b[1D\x1b[2K";
					break;
				} else {
					std::cout << "\x1b[1A\x1b[2K";
					continue;
				}
		}
		stop: // exit full loop


		// re-calculate sizes since ord_w has been updated
		delete[] sizes;
		sizes = unieqe_len(ord_w_ind, sizes_len);

		uint64_t pos_len_thrd = 1;
		for(uint32_t i=1;i<sizes_len;i++) {
			pos_len_thrd *= sizes[i];
		}
		// if there is too much data to process give warning/error
		if(pos_len_thrd > UINT32_MAX) {
			warning("Data size too large, process may not succeed");
			if(pos_len_thrd > 0xffffffffffff) { // 2^48
				// in this case, there might be a need for around 200 GB of RAM
				warning("Data size WAY TOO LARGE. Around 200GB of RAM REQUIRED in total.");
			}
		}
	} else {
		warning("Input too small, no possible word combinations found (ord_w), ordered words not established\nCannot generate possible sentences");
	}

	// write all output to out folder
	std::ofstream bigrams_txt;
	bigrams_txt.open("out/bigrams.txt");
	bigrams_txt << "bigram count: " << std::dec << possible_bigrams.size() << "\n";

	std::ofstream trigrams_txt;
	trigrams_txt.open("out/trigrams.txt");
	trigrams_txt << "trigram count: " << std::dec << possible_trigrams.size() << "\n";

	std::ofstream words_txt;
	words_txt.open("out/words.txt");
	words_txt << "word count: " << std::dec << ord_w.size() << "\n";

	std::ofstream general_data;
	general_data.open("out/data.txt");
	general_data << "len: " << len << "\nm1m2: " << hex(m1m2) << "\nct1: " << hex(ciph1) << "\nct2: " << hex(ciph2) << "\n";
	general_data.close();

	/* RESOLVED, BY STRICTENING THE ELIMINATION PROCESS USING CLI, and 2 other small comparision operations */
	// 185,131,008 amount of data to be processed, how much RAM should be in use?
	// what is the size of every possible_sentence[i]? the array has 2 13 byte values.
	// 26*memory_to_be_processed, 4,813.4062 MB per thread, running 15 threads use 60 GB of RAM,
	// but considering that empty ord_w memory allocation uses around 60-75 bytes per member
	// before initialization, the total memory is 18,698,231,808 bytes which is 18,698.2318 MB per thread,
	// for 15 threads, 280,473,477,120 bytes which is 280,473.4771 MB 
	std::cout << std::endl << "\033[32;1mPOSSIBLE_BIGRAMS:\t\033[0m";
	for(uint32_t i=0;i<possible_bigrams.size();i++) {
		bigrams_txt << possible_bigrams_ind[i] << ": {" << possible_bigrams[i][0] << ", " << possible_bigrams[i][1] << "}\n";
		std::cout << open_sq_bracket << "\x1b[37;23m" << possible_bigrams_ind[i]
				  << "\x1b[0m" << white_colon << open_curly_bracket
				  << "\033[3m" << possible_bigrams[i][0] << "\033[0m" << white_comma
				  << "\x1b[3m" << possible_bigrams[i][1] << "\x1b[0m" << closed_curly_bracket
				  << closed_sq_bracket;
	}
	std::cout << std::endl << "\033[32;1mPOSSIBLE_BIGRAMS:\t\033[0m" << std::endl
			  << "\x1b[31mpossible_bigrams count:\t\x1b[0m\033[37;1m"
			  << std::dec << possible_bigrams.size() << "\033[0m" << std::endl << "\033[32;1mPOSSIBLE_TRIGRAMS:\t\033[0m";
	for(uint32_t i=0;i<possible_trigrams.size();i++) {
		trigrams_txt << possible_trigrams_ind[i] << ": {" << possible_trigrams[i][0] << ", " << possible_trigrams[i][1] << "}\n";
		std::cout << open_sq_bracket << "\x1b[37;23m" << possible_trigrams_ind[i]
			      << "\x1b[0m" << white_colon << open_curly_bracket << "\033[3m"
				  << possible_trigrams[i][0] << "\033[0m"
				  << white_comma << "\033[3m" << possible_trigrams[i][1] << "\033[0m" << closed_curly_bracket << closed_sq_bracket;
	}
	std::cout << std::endl << "\x1b[31mpossible_trigrams count\t\x1b[0m\033[37;1m"
			  << possible_trigrams.size() << "\033[0m" << std::endl << "\033[32;1mORD_W:\t\033[0m";
	for(uint32_t i=0;i<ord_w.size();i++) {
		words_txt << ord_w_ind[i] << ": {" << ord_w[i][0] << ", " << ord_w[i][1] << "}\n";
		std::cout << open_sq_bracket << "\x1b[37;23m" << ord_w_ind[i] << "\x1b[0m" << white_colon
				  << open_curly_bracket << "\x1b[3m" << ord_w[i][0] << "\x1b[0m" << white_comma
				  << "\033[3m" << ord_w[i][1] << "\033[0m" << closed_curly_bracket << closed_sq_bracket;
	}
	std::cout << std::endl << "\x1b[31mord_w count:\t\x1b[0m\033[37;1m" << ord_w.size() << "\033[0m" << std::endl
			  << "\033[32;1mPOSSIBLE_SENTENCES_THREADS:\n\033[0m";
	uint64_t pos_len = 1;
	for(uint64_t i=0;i<sizes_len;i++) pos_len *= sizes[i];
	std::cout << std::endl << "\x1b[31mpossible_sentences count:\t\x1b[0m\033[37;1m" << pos_len
			  << "\033[0m" << std::endl;

	// close the data files
	bigrams_txt.close();
	trigrams_txt.close();
	words_txt.close();

	if (possible_words_ind.size()!=0) {
		std::string ask;
		std::cout << "\n\x1b[1;38;2;255;16;22mDo You Want to Generate All the Possible Sentences?\x1b[0m (\x1b[12;1;38;2;85;255;85my\x1b[0m/\033[1;31;13mn\033[0m)";
		std::cin >> ask;
		if(ask[0] == 'y') {
			// allocate possible_sentences pointer, on multi-threads
			// t_count equals the amount of threads required and in use, calculated as the amount of starting sylables if applicable
			// first calculate
			uint32_t t_count = sizes[0];
			std::vector<std::thread> threads(t_count);
			size_t thr_count = std::thread::hardware_concurrency()-5;

			// iterate through all threads, will work even if the amount of threads is larger than the amount
			// of threads
			uint32_t pos_start_ind = 0;
			uint32_t ord_w_i = 0;
			if(t_count >= thr_count) {
				while (t_count != t_count%thr_count) {
					for(uint32_t i=pos_start_ind;i<pos_start_ind+thr_count;i++) {
						threads[i] = std::thread(init_pos_sent, std::ref(ord_w), sizes, sizes_len, len, i, std::ref(ord_w_ind), m1m2);
						ord_w_i++;
					}
					for(uint32_t i=pos_start_ind;i<pos_start_ind+thr_count;i++) threads[i].join();

					t_count -= thr_count;
					pos_start_ind += thr_count;
				}
			}
			
			// iterate the threads that are left (non-multiple of thr_count)
			uint32_t cond = t_count%thr_count;
			if(cond != 0) {
				for(uint32_t i=pos_start_ind;i<cond;i++) {
					threads[i] = std::thread(init_pos_sent, std::ref(ord_w), sizes, sizes_len, len, i, std::ref(ord_w_ind), m1m2);
				}
				for(uint32_t i=pos_start_ind;i<cond;i++) threads[i].join();
				t_count -= cond;
			}
		} else {
			std::cout << "\nfinished cracking the OneTimePad Ciphertexts\n";
		}

		delete[] sizes;
	}
	return 0;

	// The if the plaintext starts with a non-common letter, it doesn't get used
	// when using random words, this elimination process deleted around 50% of the output while
	// when using bigrams, this elimination process only deleted 2 possible bigrams
}

