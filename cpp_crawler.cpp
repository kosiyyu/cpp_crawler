#include "cpp_crawler.h"
#include "parser.hpp"
#include <chrono>

size_t callback_func(char* buff, size_t chunk_size, size_t n, std::string* str) {
	size_t real_bytes = chunk_size * n;
	str->append(buff, real_bytes);
	//std::cout << "chunk: " << real_bytes << ", " << chunk_size << ", " << n << std::endl;
	return real_bytes;
}

int main()
{
	std::string html_string;

	//auto start_time = std::chrono::high_resolution_clock::now();

	const auto &curl= curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "https://www.reddit.com/r/books/comments/16qvziw/just_read_catcher_in_the_rye_im_confused/"); 
	//https://www.reddit.com/r/books/hot/ 
	// https://www.reddit.com/r/books/comments/16qu49m/did_a_book_forced_on_you_at_school_put_you_off_it/
	// https://www.reddit.com/r/books/comments/16qvziw/just_read_catcher_in_the_rye_im_confused/
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/117.0");
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_func);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html_string);
	const auto &resp = curl_easy_perform(curl);
	// todo handle errors or sth
	curl_easy_cleanup(curl);

	//auto end_time = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

	//std::cout << "time: " << duration.count() << " milliseconds or " << duration.count() / (double)1000 << " second" << std::endl;

	//std::cout << html_string;

	//GumboOutput* output = gumbo_parse("<h1>Hello, World!</h1>");
	////std::cout << typeid(output->root->type).name();
	//output->root.
	//gumbo_destroy_output(&kGumboDefaultOptions, output);
	Parser parser(html_string);
	parser.extract_data();













	return 0;
}

// https://curl.se/libcurl/c/libcurl-tutorial.html
