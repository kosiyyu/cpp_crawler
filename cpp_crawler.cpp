#include "cpp_crawler.h"
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
	curl_easy_setopt(curl, CURLOPT_URL, "https://www.reddit.com/");
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/117.0");
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_func);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html_string);
	const auto &resp = curl_easy_perform(curl);

	//auto end_time = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

	//std::cout << "time: " << duration.count() << " milliseconds or " << duration.count() / (double)1000 << " second" << std::endl;

	//std::cout << html_string;
	return 0;
}

// https://curl.se/libcurl/c/libcurl-tutorial.html
