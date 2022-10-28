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
#include <string>
#include <iomanip>
#include <sstream>
#include <map>
#include <array>
#include <vector>
#include <set>
#include <iterator>
#include <thread>
#include <algorithm>
#include <stdexcept>
#include <fstream>

#if __cplusplus <= 201703L
	#error "C++ version is not required version, C++20 required"
#endif

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

std::string hex(std::string inp)
{
	std::stringstream ss;
	for(unsigned int i=0;i<inp.length();i++) ss << std::hex << std::setfill('0') << std::setw(2) << (inp[i]+0);
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
	unsigned int len = msg.length()-val.length();
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
																				 strv, uint32_t elem) {
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

class warning : public std::exception
{
	private:
	     std::string msg;
	public:
	     warning(const std::string& msg) {};
	     inline const char* what() {return msg.c_str();}
};

/*
// algorithm to find n, the amount of loops
// indexes are indexes from the nested loops of test_all_prototype()
uint32_t find_n(std::vector<uint32_t> indexes, uint32_t ciph_len) {
	uint32_t tmp = 0, n = 0;
	for(uint32_t i=0;indexes.size();i++) {
		if (tmp <= ciph_len) {
			tmp += ord_w[indexes[i]][0].length();
		} else {
			n = i;
			break;
		}
	}
	return n;
}

// do not run, this is for reference to better understand the loop function defined ahead
// variable len calculated in unieqe_len() is the number of nested loops
void test_all_prototype(uint32_t n, uint32_t ciph_len, std::vector<std::array<std::string, 2>> &possible_sentences) {
	possible_sentences.reserve(n*ord_w.size());
	// TODO: the starting values should be lens[0], lens[1]... otherwise, it will create sentences
	// using 0th index + 0th index
	
	// calculate initial value of n
	std::vector<uint32_t> initial_indexes.reserve(lens.size());
	for(uint32_t i=0;i<lens.size();i++) {
		initial_indexes.push_back(lens[i]);
	}
	n = find_n(initial_indexes, ciph_len);
	
	for(uint32_t i=0;i<ord_w_ind.size();i++) {
		for(uint32_t j=1;j<ord_w_ind.size();j++) {
			for(uint32_t k=2;k<ord_w_ind.size();k++) {
				for(uint32_t x=3;x<ord_w_ind.size();x++) {
					for(uint32_t z=4;z<ord_w_ind.size();z++) {
						for(uint32_t b=5;b<ord_w_ind.size();b++) { // if n = 7, the amount of ord_w[...] should add to length of ciphertext
							for(uint32_t f=6;f<ord_w_ind.size();f++) {
								std::string add = ord_w[i][0] + ord_w[j][0] + ord_w[k][0] + 
											  	  ord_w[x][0] + ord_w[z][0] + ord_w[b][0] + ord_w[f][0];
								std::array<std::string,2> arr = {add, ord_w[i][1] + ord_w[j][1] +
																 ord_w[k][1] + ord_w[x][1] +
																 ord_w[z][1] + ord_w[b][1] + ord_w[f][1]};
								possible_sentences.push_back(arr);
								
								// re-calculate n for the next iteration
								// this needs to happen because not all the lengths of plaintexts are the same
								std::vector<uint32_t> indexes{i,j,k,x,z,b,f};
								n = find_n(indexes, ciph_len);
								
								// use indexes vector for re-looping from indexes[...]+=1;
								// plus/minus the difference of n loops
								
							}
						}
					}
				}
			}
		}
	}
}
*/

#pragma GCC diagnostic ignored "-Wreturn-type"
// recursive loop algorithm for trying every sentence combination
bool loop(std::vector<std::array<std::string, 2>> &possible_sentences, std::vector<uint32_t> &lens,
		  uint32_t &n, std::string &tmp_str1, std::string &tmp_str2, uint32_t &ciph_len, uint32_t
		  &start_ind, std::vector<std::array<std::string, 2>> &ord_w)
{
	if(n == 0) {
		return 1; // recursion exit code
	} else {
    	for(uint32_t i=start_ind;i<n;i++) {
			if(tmp_str1.length() < ciph_len) {
					tmp_str1 += ord_w[start_ind][0];
			tmp_str2 += ord_w[start_ind][1];
			start_ind = lens[i];
			} else {
				possible_sentences.push_back({tmp_str1, tmp_str2});
				tmp_str1 = "";
				tmp_str2 = "";

			}
			n--;
        	loop(possible_sentences, lens, n, tmp_str1, tmp_str2, ciph_len, start_ind, ord_w);
	    }
	}
}

bool it_lens(std::vector<std::array<std::string, 2>> &possible_sentences, std::vector<uint32_t> &lens,
		  uint32_t &i, std::string &tmp_str1, std::string &tmp_str2, uint32_t &ciph_len, uint32_t
		  &start_ind, std::vector<std::array<std::string, 2>> &ord_w)
{
	if(i < lens.size()) {
		for(uint32_t j=0;j<lens[i];j++) {
			
		}
	} else {
		return 1;
	}
}
#pragma GCC diagnostic pop

// function for declaring pointers for calculating possible sentences using multi-threading
inline void init_pos_sent(std::array<std::string, 2> *&possible_sentences_i, uint32_t pos_sent_len, uint32_t ind,
						  std::vector<std::array<std::string, 2>> &ord_w)
{
	possible_sentences_i = new std::array<std::string, 2>[pos_sent_len];
	
	// add all the possible_sentences first syllable
	// every first syllable gets their own thread if applicable 
	for(uint32_t j=0;j<pos_sent_len;j++) {
		possible_sentences_i[j][0] = ord_w[ind][0];
		possible_sentences_i[j][1] = ord_w[ind][1];
	}
}

inline void print_ord_w(std::vector<std::array<std::string, 2>> ord_w, std::vector<uint32_t> ord_w_ind)
{
	std::cout << std::endl << "ORD_W:\t";
	for(uint32_t i=0;i<ord_w.size();i++) {
		std::cout << "(i:" << i << " - [" << ord_w_ind[i] << ": {" << ord_w[i][0] << ", "
				  << ord_w[i][1] << "}]) ";
	}
	std::cout << std::endl << "ord_w count:\t" << ord_w.size() << std::endl;
}

int main(int argc, char *argv[])
{
	const std::string m1 = "thetestvector";
	const std::string m2 = "non-sensecode";
	const uint32_t len = m1.length(); // 13
	std::shared_ptr<uint8_t> key = gen_priv_key(len);
	std::cout << std::endl << "M1:\t" << hex(m1) << std::endl << "M2:\t" << hex(m2) << std::endl << "KEY:\t";
	for(uint32_t i=0;i<len;i++) {
		std::cout << std::setfill('0') << std::setw(2) << std::hex << key.get()[i]+0;
	}
	std::cout << std::endl;
	
	// encrypt messages using one time pad
	std::string ciph1 = one_time_pad<std::shared_ptr<uint8_t>>(m1, key, len);
	std::string ciph2 = one_time_pad<std::shared_ptr<uint8_t>>(m2, key, len);
	std::string m1m2 = one_time_pad<std::string>(ciph1, ciph2, len);
	std::string eq = one_time_pad<std::string>(m1,m2,len);
	std::cout << std::endl << "C1:\t" << hex(ciph1) << std::endl << "C2:\t" << hex(ciph2)
			  << std::endl << "M1M2:\t" << std::flush << hex(m1m2) << std::endl << "EQ:\t"
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

	const unsigned int bi_i = len-2;
	const constexpr unsigned int bi_len = sizeof(bigram)/sizeof(bigram[0]);
	const unsigned int tri_i = len-3;
	const constexpr unsigned int tri_len = sizeof(trigram)/sizeof(trigram[0]);
	const constexpr unsigned int word_len = std::size(words);

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
				std::cout << tmp; // if tmp = bigram[i], it is correct

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
		std::string *tries = try_all(m1m2, words[i]);
		std::cout << std::endl << "FOR STRING \"" << words[i] << "\" TRY1:\t\t\t";
		for(unsigned int j=0;j<len-words[i].length();j++) std::cout << tries[j] << " ";

		// calculate second plaintext based on tries on calculating first plaintext, which can
		// be anything
		std::cout << std::endl << "FOR STRING ^ABOVE^ TRY2:\t\t\t";
		for(unsigned int j=0;j<len-words[i].length();j++) {
			bool valid_tries = false;
			for(unsigned int k=0;k<word_len;k++) {
				valid_tries = words[k].find(tries[j]) != std::string::npos;
				if (valid_tries) break;
			}
			if (valid_tries) {
				std::string tmp = one_time_pad<std::string>(tries[j], m1m2.substr(j,words[i].length()),
															words[i].length());
				std::cout << tmp;
	
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

	uint32_t max = *max_element(possible_words_ind.begin(), possible_words_ind.end());
	uint32_t index = 0;

	std::vector<std::array<std::string, 2>> ord_w;
	std::vector<uint32_t> ord_w_ind;
	
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
	uint32_t sizes_len;
	uint32_t *sizes = unieqe_len(ord_w_ind, sizes_len);

	//////////////// EXTRA ELIMINITAION-PROCESSES TO SAVE MEMORY AND TIME ////////////////
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
	
	// CLI for removing certain values based on how much they make sense to the user after
	// concatination of ord_w elements
	while((bool)argv[1][0]) {
		print_ord_w(ord_w, ord_w_ind);
		size_t n = 0;
		for(uint32_t v=0;v<sizes[n];v++) {
			std::array<std::string, 2> *comb = new std::array<std::string, 2>[sizes[n]];
			for(uint32_t j=sizes[n];j<sizes[n]+sizes[n+1];j++) {
				comb[v][0] = ord_w[v][0] + ord_w[j][0];
				comb[v][1] = ord_w[v][1] + ord_w[j][1];
				std::cout << "\ncombination = [" << comb[v][0] << " : " << comb[v][1]
						   << "\t-1:" << v << "\t-2:" << j << "]";
			}
			while(true) {
				std::string input = "";
				std::cout << std::endl << "input index to remove or to see certain values:\t";
				std::getline(std::cin, input);
				if(input == "" or input.find("help") != std::string::npos) {
					system("cat help.json");
				} else if(std::all_of(input.begin(),input.end(), [](char inp) {return isdigit(inp);})) {
					uint32_t digit = static_cast<uint32_t>(std::stoul(input));
					if(digit < ord_w.size()) {
						ord_w.erase(ord_w.begin()+digit);
						ord_w_ind.erase(ord_w_ind.begin()+digit);
					} else {
						std::cout << std::endl << "input too large, has to be smaller than "
								  << ord_w.size();
					}
				} else if(input.starts_with("see")) {
					if(std::any_of(input.begin(),input.end(), [](char inp) {return inp == 'o';})) { // print ord_w
						print_ord_w(ord_w, ord_w_ind);
					} else if(std::any_of(input.begin(),input.end(), [](char inp) {return inp == 'l';})) { // print sizes
						sizes = unieqe_len(ord_w_ind, sizes_len);
						std::cout << "\nsizes:\t[";
						for(uint32_t i=0;i<sizes_len;i++) {
							std::cout << sizes[i];
							if(i < sizes_len-1) {
								std::cout << ", ";
							}
						}
						std::cout << "]" << std::endl;
					} else if(std::any_of(input.begin(),input.end(), [](char inp) {return inp == 'n';})) { // print n
							std::cout << std::endl << "n:" << n << " - " << sizes_len-1-n
									  << " amount of iterations left, type \"c\" to continue loop"
									  << " and increment n, type \"r\" to reset n to 0 and re-loop";
					} else if(std::any_of(input.begin(), input.end(), [](char inp) {return inp == 'c';})) { // print comb
						sizes = unieqe_len(ord_w_ind, sizes_len);
						std::cout << std::endl << "combinations:\t{\n";

						// re-calculate comb since ord_w might be updated
						for(uint32_t j=sizes[n];j<sizes[n]+sizes[n+1];j++) {
							comb[v][0] = ord_w[v][0] + ord_w[j][0];
							comb[v][1] = ord_w[v][1] + ord_w[j][1];
							std::cout << "\ncombination = [" << comb[v][0] << " : " << comb[v][1]
									  << "\t-1:" << v << "\t-2:" << j << "]";
						}
						std::cout << std::endl << "}";
					} else {
						std::cout << std::endl << "Warning: see - invalid sub-command";
					}
				} else if(input == "q") {
					std::cout << "\nare you sure you want to quit? (y/n) ";
					char verify;
					std::cin >> verify;
					if (verify == 'y') {
						goto loop1;
					}
				} else if(input == "exit") {
					goto stop;
				} else if(input == "c") { // continue the loop, by increasing n
					if(n<sizes_len-1) {
						n++;
					} else {
						std::cout << "\ncombinations iteration done, type \"r\" to reset it, type \"exit\" to exit";
					}
					delete[] comb;
					goto first_for_loop;
				} else if(input == "r") {
					n = 0;
				} else {
					system("cat help.json");
				}
			}
			first_for_loop:
				continue;
		}
		loop1:
			std::cout << "exit? (y/n) ";
			char verify;
			std::cin >> verify;
			if (verify == 'y') {
				break;
			} else {
				continue;
			}
	}
	stop:


	// re-calculate sizes since ord_w has been updated
	sizes = unieqe_len(ord_w_ind, sizes_len);

	uint64_t pos_len_thrd = 1;
	for(uint32_t i=1;i<sizes_len;i++) {
		pos_len_thrd *= sizes[i];
	}
	
	// if there is too much data to process give warning/error
	if(pos_len_thrd > UINT32_MAX) {
		std::cerr << "\nData size too large, process may not succeed";
		if(pos_len_thrd > 0xffffffffffff) { // uint48_t size
			// in this case, there might be a need for around 200 GB of RAM
			throw std::overflow_error("\ndata size cannot be processed without a supercomputer");
		}
	}

	//////////////// RESOLVED, BY STRICTENING THE ELIMINATION PROCESS USING SECOND EXE FILE ////////////////
	// 185,131,008 amount of data to be processed, how much RAM should be in use?
	// what is the size of every possible_sentence[i]? the array has 2 13 byte values.
	// 26*memory_to_be_processed, 4,813.4062 MB per thread, running 15 threads use 60 GB of RAM,
	// but considering that empty ord_w memory allocation uses around 60-75 bytes per member
	// before initialization, the total memory is 18,698,231,808 bytes which is 18,698.2318 MB MB per thread,
	// for 15 threads, 280,473,477,120 bytes which is 280,473.4771 MB 

	// allocate possible_sentences pointer, on multi-threads
	// t_count equals the amount of threads in use, calculated as the amount of starting sylables if applicable
	// first calculate
	uint32_t t_count = sizes[0];
	std::array<std::string, 2> **possible_sentences_threads = new std::array<std::string, 2> *[sizes[0]];
	std::vector<std::thread> threads(t_count);
	size_t thr_count = std::thread::hardware_concurrency()-5;

	// iterate through all threads, will work even if the amount of threads is larger than the amount
	// of threads
	uint32_t pos_start_ind = 0;
	uint32_t ord_w_i = 0;
	if(t_count >= thr_count) {
		while (t_count != t_count%thr_count) {
			for(uint32_t i=pos_start_ind;i<pos_start_ind+thr_count;i++) {
				threads[i] = std::thread(init_pos_sent, std::ref(possible_sentences_threads[i]),
										 pos_len_thrd, ord_w_i, std::ref(ord_w));
				ord_w_i++;
			}
			for(uint32_t i=pos_start_ind;i<pos_start_ind+thr_count;i++) threads[i].join();

			t_count -= thr_count;
			pos_start_ind += thr_count;
		}
	}
	
	// iterate the threads that are left (non-multiple of thr_count)
	uint32_t cond = 0;//t_count%thr_count;
	if(cond != 0) {
		for(uint32_t i=pos_start_ind;i<cond;i++) {
			threads[i] = std::thread(init_pos_sent, std::ref(possible_sentences_threads[i]),
									 pos_len_thrd, ord_w_i, std::ref(ord_w));
		}
		
		for(uint32_t i=pos_start_ind;i<cond;i++) threads[i].join();
		t_count -= cond;
	}
	
	//std::string tmp_str1 = "";
	//std::string tmp_str2 = "";
	//uint32_t start_i = 1;
	//uint32_t ord_w_size = ord_w.size();
	// loop(possible_sentences[i], ord_w_ind, ord_w_size, tmp_str1, tmp_str2, len, start_i, ord_w);
	// it_lens(possible_sentences_threads, ord_w_ind, start_i, tmp_str1, tmp_str2, len, start_i, ord_w);
	// LENS IS NOT EQUAL TO ORD_W_IND
	
	std::cout << std::endl << "POSSIBLE_BIGRAMS:\t";
	for(uint32_t i=0;i<possible_bigrams.size();i++) {
		std::cout << "[" << possible_bigrams_ind[i] << ": {" << possible_bigrams[i][0] << ", " 
				  << possible_bigrams[i][1]  << "}] ";
	}
	std::cout << std::endl << "POSSIBLE_BIGRAMS:\t" << std::endl << "possible_bigrams count:\t"
			  << std::dec << possible_bigrams.size() << std::endl << "POSSIBLE_TRIGRAMS:\t";
	for(uint32_t i=0;i<possible_trigrams.size();i++) {
		std::cout << "[" << possible_trigrams_ind[i] << ": {" << possible_trigrams[i][0] << ", "
				  << possible_trigrams[i][1] << "}] ";
	}
	std::cout << std::endl << "possible_trigrams count\t" << possible_trigrams.size() << std::endl
			  << "ORD_W:\t";
	for(uint32_t i=0;i<ord_w.size();i++) {
		std::cout << "[" << ord_w_ind[i] << ": {" << ord_w[i][0] << ", "
				  << ord_w[i][1] << "}] ";
	}
	std::cout << std::endl << "ord_w count:\t" << ord_w.size() << std::endl
			  << "POSSIBLE_SENTENCES_THREADS:\n";
	for(uint32_t i=0;i<t_count;i++) {
		for(uint32_t j=0;j<pos_len_thrd;j++)
			std::cout << "[" << possible_sentences_threads[i][j][0] << ",\n"
					  << possible_sentences_threads[i][j][1] << "]" << std::endl;
	}
	uint64_t pos_len = 1;
	for(uint64_t i=0;i<sizes_len;i++) pos_len *= sizes[i];
	std::cout << std::endl << "possible_sentences count:\t" << pos_len
			  << std::endl;
	delete[] sizes;
	for(size_t i=0;i<t_count;i++) delete[] possible_sentences_threads[i];
	delete[] possible_sentences_threads;
	return 0;

	// The if the plaintext starts with a non-common letter, it doesn't get used
	// when using random words, this elimination process deleted around 50% of the output while
	// when using bigrams, this elimination process only deleted 2 possible bigrams
}

