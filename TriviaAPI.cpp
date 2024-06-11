#include "TriviaAPI.h"

size_t write_data(void* ptr, size_t size, size_t nmemb, void* userdata) {
    ((std::string*)userdata)->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

std::vector<Question> TriviaAPI::get_questions(const Category& category, const std::string& difficulty) {
    std::vector<Question> questions;

    CURL* curl = curl_easy_init();
    if (curl) {
        std::string responce;
        std::string url = base_url + std::to_string(category.get_id()) + "&difficulty=" + difficulty + "&type=multiple";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responce);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            nlohmann::json data = nlohmann::json::parse(responce);

            const auto& results = data["results"];
            for (const auto& result : results) {
                Question question;
                question.set_type(result["type"]);
                question.set_category(category);
                question.set_difficulty(result["difficulty"]);
                question.set_question(result["question"]);
                question.set_correct_answer(result["correct_answer"]);
                question.set_incorrect_answers(result["incorrect_answers"]);

                questions.push_back(question);
            }
        }

        curl_easy_cleanup(curl);
    }
    return questions;
}

std::vector<Question> TriviaAPI::get_questions() {
    std::vector<Question> questions;

    CURL* curl = curl_easy_init();
    if (curl) {
        std::string responce;
        std::string url = "https://opentdb.com/api.php?amount=5&type=multiple";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responce);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            nlohmann::json data = nlohmann::json::parse(responce);

            const auto& results = data["results"];
            for (const auto& result : results) {
                Question question;
                question.set_type(result["type"]);
                question.set_category(category_initializer(result["category"]));
                question.set_difficulty(result["difficulty"]);
                question.set_question(result["question"]);
                question.set_correct_answer(result["correct_answer"]);
                question.set_incorrect_answers(result["incorrect_answers"]);

                questions.push_back(question);
            }
        }

        curl_easy_cleanup(curl);
    }
    return questions;
}

void TriviaAPI::download_categories() {
    CURL* curl = curl_easy_init();

    if (curl) {
        std::string responce;
        std::string url = "https://opentdb.com/api_category.php";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responce);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            nlohmann::json data = nlohmann::json::parse(responce);

            const auto& results = data["trivia_categories"];
            for (const auto& category : results) {
                std::string category_name = category["name"];
                int category_id = category["id"];
                categories.push_back(Category(category_name, category_id));
            }
        }

        curl_easy_cleanup(curl);
    }

}

void TriviaAPI::show_categories() {
    std::cout << "\n\n\tCategories:" << std::endl;
    for (const Category& category : categories) {
        std::cout << "\n\n\t" << std::left << std::setw(45) << category.get_name() << "Code :" << category.get_id() << std::endl;
    }
}

std::vector<Category> TriviaAPI::get_categories() const {
    return categories;
}

Category TriviaAPI::category_initializer(const std::string& category_name) {
    for (const Category& category : categories) {
        if (category.get_name() == category_name) {
            return category;
        }
    }
}
