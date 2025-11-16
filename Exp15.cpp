#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <thread>
#include <map>
#include <sstream>

using namespace std;

struct Question {
    string question;
    vector<string> options;
    int correctOption;
};

// Forward declarations
void clearScreen();
int showMainMenu();
void takeQuiz();
vector<Question> loadQuestions();
void generateFromKeywords();

// Sample question bank organized by categories
map<string, vector<Question>> questionBank = {
    {"science", {
        {"What is the chemical symbol for water?", {"H2O", "CO2", "NaCl", "O2"}, 1},
        {"Which planet is known as the Red Planet?", {"Venus", "Mars", "Jupiter", "Saturn"}, 2},
        {"What is the powerhouse of the cell?", {"Nucleus", "Mitochondria", "Ribosome", "Golgi"}, 2},
        {"What is the atomic number of Carbon?", {"4", "6", "8", "12"}, 2},
        {"Which gas is most abundant in Earth's atmosphere?", {"Oxygen", "Carbon Dioxide", "Nitrogen", "Argon"}, 3},
        {"What is the speed of light in vacuum (m/s)?", {"3x10^5", "3x10^6", "3x10^8", "3x10^10"}, 3},
        {"Which element has the chemical symbol 'Au'?", {"Silver", "Gold", "Aluminum", "Argon"}, 2},
        {"What is the hardest natural substance on Earth?", {"Gold", "Iron", "Diamond", "Platinum"}, 3},
        {"Which planet is known as the Morning Star?", {"Venus", "Mars", "Jupiter", "Mercury"}, 1},
        {"What is the chemical formula of table salt?", {"NaCl", "H2O", "CO2", "C6H12O6"}, 1},
        {"Which is the largest organ of the human body?", {"Liver", "Brain", "Skin", "Heart"}, 3},
        {"What is the pH value of pure water?", {"5", "6", "7", "8"}, 3},
        {"Which gas do plants absorb during photosynthesis?", {"Oxygen", "Carbon Dioxide", "Nitrogen", "Hydrogen"}, 2},
        {"What is the unit of electrical resistance?", {"Volt", "Ampere", "Ohm", "Watt"}, 3},
        {"Which planet has the most moons in our solar system?", {"Jupiter", "Saturn", "Neptune", "Uranus"}, 2},
        {"What is the chemical symbol for gold?", {"Ag", "Au", "Fe", "Pb"}, 2},
        {"Which blood type is the universal donor?", {"A", "B", "AB", "O"}, 4},
        {"What is the largest planet in our solar system?", {"Earth", "Jupiter", "Saturn", "Neptune"}, 2},
        {"Which vitamin is produced when the human body is exposed to sunlight?", {"A", "B", "C", "D"}, 4},
        {"What is the chemical formula for ozone?", {"O2", "O3", "CO2", "H2O"}, 2}
    }},
    {"history", {
        {"In which year did World War II end?", {"1943", "1945", "1950", "1939"}, 2},
        {"Who was the first President of the United States?", 
            {"Thomas Jefferson", "George Washington", "John Adams", "Abraham Lincoln"}, 2},
        {"Which ancient civilization built the Great Pyramids?", {"Greeks", "Romans", "Egyptians", "Mayans"}, 3},
        {"Who painted the Mona Lisa?", {"Vincent van Gogh", "Pablo Picasso", "Leonardo da Vinci", "Michelangelo"}, 3},
        {"In which year did the Titanic sink?", {"1905", "1912", "1918", "1923"}, 2},
        {"Who was the first person to step on the Moon?", {"Neil Armstrong", "Buzz Aldrin", "Yuri Gagarin", "Alan Shepard"}, 1},
        {"Which empire was ruled by Genghis Khan?", {"Roman", "Mongol", "Ottoman", "British"}, 2},
        {"When was the Declaration of Independence signed?", {"1776", "1789", "1792", "1801"}, 1},
        {"Who was the first female Prime Minister of the UK?", {"Theresa May", "Margaret Thatcher", "Indira Gandhi", "Angela Merkel"}, 2},
        {"Which ancient wonder was located in Alexandria, Egypt?", {"Hanging Gardens", "Colossus of Rhodes", "Lighthouse of Alexandria", "Great Pyramid"}, 3},
        {"Who wrote 'The Art of War'?", {"Sun Tzu", "Confucius", "Lao Tzu", "Mencius"}, 1},
        {"In which year did the Berlin Wall fall?", {"1985", "1989", "1991", "1995"}, 2},
        {"Who was the first emperor of Rome?", {"Julius Caesar", "Augustus", "Nero", "Caligula"}, 2},
        {"Which war was fought between the North and South regions of the US?", {"Revolutionary War", "War of 1812", "Civil War", "Spanish-American War"}, 3},
        {"Who discovered America in 1492?", {"Christopher Columbus", "Vasco da Gama", "Ferdinand Magellan", "Marco Polo"}, 1},
        {"Which ancient city was destroyed by the eruption of Mount Vesuvius?", {"Athens", "Pompeii", "Sparta", "Troy"}, 2},
        {"Who was the first woman to win a Nobel Prize?", {"Marie Curie", "Mother Teresa", "Rosalind Franklin", "Jane Addams"}, 1},
        {"Which country was the first to give women the right to vote?", {"USA", "UK", "New Zealand", "France"}, 3},
        {"Who was the last Tsar of Russia?", {"Peter the Great", "Ivan the Terrible", "Nicholas II", "Alexander II"}, 3},
        {"In which year did World War I begin?", {"1912", "1914", "1916", "1918"}, 2}
    }},
    {"programming", {
        {"What does 'OOP' stand for?", 
            {"Object-Oriented Programming", "Object-Oriented Process", "Object-Oriented Protocol", "Object-Oriented Project"}, 1},
        {"Which language is known as the 'mother of all languages'?", 
            {"C", "Java", "Python", "Assembly"}, 1},
        {"What does HTML stand for?", 
            {"Hyper Text Markup Language", "High Tech Modern Language", "Hyperlink and Text Markup Language", "Home Tool Markup Language"}, 1},
        {"Which of these is not a programming language?", {"Java", "Python", "HTML", "Ruby"}, 3},
        {"What is the correct way to declare a variable in Python?", 
            {"variable name = value", "var name = value", "name = value", "String name = value"}, 3},
        {"Which data structure uses LIFO (Last In First Out) principle?", 
            {"Queue", "Stack", "Array", "Linked List"}, 2},
        {"What is the output of 'print(2 ** 3)' in Python?", {"6", "8", "9", "23"}, 2},
        {"Which of these is not a valid variable name in most programming languages?", 
            {"my_var", "2ndVar", "_private", "$amount"}, 2},
        {"What does API stand for?", 
            {"Application Programming Interface", "Advanced Programming Interface", "Automated Program Interaction", "Application Process Integration"}, 1},
        {"Which language is used for styling web pages?", {"HTML", "CSS", "JavaScript", "PHP"}, 2},
        {"What is the correct syntax for an if statement in Python?", 
            {"if x > y:", "if (x > y) then", "if x > y then", "if {x > y}"}, 1},
        {"Which symbol is used for single-line comments in Python?", {"//", "#", "/*", "--"}, 2},
        {"What is the correct way to create a function in JavaScript?", 
            {"function = myFunction()", "function myFunction()", "def myFunction()", "function:myFunction()"}, 2},
        {"Which of these is not a JavaScript framework?", {"React", "Angular", "Django", "Vue"}, 3},
        {"What does SQL stand for?", 
            {"Structured Query Language", "Simple Query Language", "Standard Query Language", "Sequential Query Language"}, 1},
        {"Which of these is not a valid data type in Python?", {"int", "float", "string", "character"}, 4},
        {"What is the correct way to create an array in JavaScript?", 
            {"array = []", "array = {}", "array = ()", "array = new Array()"}, 1},
        {"Which operator is used for exponentiation in Python?", {"^", "**", "^^", "*^"}, 2},
        {"What does CSS stand for?", 
            {"Computer Style Sheets", "Creative Style Sheets", "Cascading Style Sheets", "Colorful Style Sheets"}, 3},
        {"Which of these is not a version control system?", {"Git", "SVN", "Mercurial", "Maven"}, 4}
    }},
    {"geography", {
        {"What is the capital of France?", {"London", "Berlin", "Paris", "Madrid"}, 3},
        {"Which is the longest river in the world?", {"Nile", "Amazon", "Yangtze", "Mississippi"}, 1},
        {"Which country has the largest population in the world?", {"India", "USA", "China", "Indonesia"}, 3},
        {"What is the largest ocean on Earth?", {"Atlantic", "Indian", "Arctic", "Pacific"}, 4},
        {"Which country is home to the Great Barrier Reef?", {"Brazil", "Australia", "Thailand", "Mexico"}, 2},
        {"What is the capital of Japan?", {"Beijing", "Seoul", "Tokyo", "Bangkok"}, 3},
        {"Which desert is the largest in the world?", {"Sahara", "Arabian", "Gobi", "Kalahari"}, 1},
        {"What is the smallest continent by land area?", {"Europe", "Australia", "Antarctica", "South America"}, 2},
        {"Which mountain is the highest in the world?", {"K2", "Kangchenjunga", "Mount Everest", "Lhotse"}, 3},
        {"Which country is known as the Land of the Rising Sun?", {"China", "South Korea", "Japan", "Vietnam"}, 3},
        {"What is the capital of Canada?", {"Toronto", "Vancouver", "Ottawa", "Montreal"}, 3},
        {"Which river flows through the Grand Canyon?", {"Mississippi", "Colorado", "Rio Grande", "Missouri"}, 2},
        {"What is the largest country by land area?", {"USA", "China", "Canada", "Russia"}, 4},
        {"Which city is located on two continents?", {"Istanbul", "Moscow", "Cairo", "Dubai"}, 1},
        {"What is the capital of Brazil?", {"Rio de Janeiro", "Sao Paulo", "Brasilia", "Buenos Aires"}, 3},
        {"Which African country was formerly known as Abyssinia?", {"Ethiopia", "Ghana", "Kenya", "Tanzania"}, 1},
        {"What is the largest island in the world?", {"Borneo", "Greenland", "Madagascar", "New Guinea"}, 2},
        {"Which country is the largest producer of coffee in the world?", {"Brazil", "Colombia", "Vietnam", "Indonesia"}, 1},
        {"What is the capital of South Africa?", {"Cape Town", "Johannesburg", "Pretoria", "Durban"}, 3},
        {"Which sea is the saltiest body of water on Earth?", {"Dead Sea", "Red Sea", "Black Sea", "Caspian Sea"}, 1}
    }},
    {"sports", {
        {"In which sport would you perform a slam dunk?", {"Basketball", "Tennis", "Soccer", "Volleyball"}, 1},
        {"Which country won the 2018 FIFA World Cup?", {"Germany", "Brazil", "France", "Croatia"}, 3},
        {"How many players are there in a standard soccer team?", {"9", "10", "11", "12"}, 3},
        {"Which sport uses terms like 'love' and 'deuce'?", {"Tennis", "Golf", "Cricket", "Badminton"}, 1},
        {"In which country were the first Olympic Games held?", {"Rome", "Athens", "Olympia", "Sparta"}, 3},
        {"Which athlete has won the most Olympic gold medals?", {"Michael Phelps", "Usain Bolt", "Carl Lewis", "Larisa Latynina"}, 1},
        {"In which sport would you perform a 'hole in one'?", {"Golf", "Tennis", "Basketball", "Baseball"}, 1},
        {"Which country won the first ever Cricket World Cup in 1975?", {"England", "West Indies", "Australia", "India"}, 2},
        {"How many players are there in a standard baseball team on the field?", {"7", "8", "9", "10"}, 3},
        {"Which country hosted the 2016 Summer Olympics?", {"Japan", "Brazil", "UK", "China"}, 2},
        {"In tennis, what is a score of 40-40 called?", {"Deuce", "Advantage", "Match Point", "Set Point"}, 1},
        {"Which sport is associated with Wimbledon?", {"Golf", "Tennis", "Cricket", "Rugby"}, 2},
        {"How many players are there in a standard cricket team on the field?", {"9", "10", "11", "12"}, 3},
        {"Which country has won the most FIFA World Cups?", {"Germany", "Italy", "Brazil", "Argentina"}, 3},
        {"In which sport would you use a 'birdie'?", {"Badminton", "Golf", "Tennis", "Table Tennis"}, 1},
        {"How many players are there in a standard volleyball team on the court?", {"5", "6", "7", "8"}, 2},
        {"Which country won the most medals in the 2020 Tokyo Olympics?", {"USA", "China", "Japan", "Great Britain"}, 1},
        {"In which sport would you perform a 'home run'?", {"Basketball", "Baseball", "Cricket", "Hockey"}, 2},
        {"Which country has won the most Olympic gold medals in history?", {"USA", "Soviet Union", "Germany", "Great Britain"}, 1},
        {"How many players are there in a standard rugby union team on the field?", {"13", "14", "15", "16"}, 3}
    }}
};

// Function to generate questions based on keywords
vector<Question> generateQuestions(const string& keyword, int count) {
    vector<Question> generatedQuestions;
    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);
    
    // Search in all categories
    for (const auto& category : questionBank) {
        for (const auto& question : category.second) {
            string questionText = question.question;
            transform(questionText.begin(), questionText.end(), questionText.begin(), ::tolower);
            
            if (questionText.find(lowerKeyword) != string::npos) {
                generatedQuestions.push_back(question);
                if (generatedQuestions.size() >= static_cast<size_t>(count)) {
                    return generatedQuestions;
                }
            }
        }
    }
    
    // If not enough questions found with keyword, add some from the same category
    for (const auto& category : questionBank) {
        if (lowerKeyword.find(category.first) != string::npos) {
            for (const auto& question : category.second) {
                if (find(generatedQuestions.begin(), generatedQuestions.end(), question) == generatedQuestions.end()) {
                    generatedQuestions.push_back(question);
                    if (generatedQuestions.size() >= static_cast<size_t>(count)) {
                        return generatedQuestions;
                    }
                }
            }
        }
    }
    
    return generatedQuestions;
}

void clearScreen() {
    system("cls");
}

int showMainMenu() {
    clearScreen();
    cout << "\n=== QUIZ GENERATOR ===\n";
    cout << "[1] Create New Quiz\n";
    cout << "[2] Generate from Keywords\n";
    cout << "[3] Manage Questions\n";
    cout << "[4] View Statistics\n";
    cout << "[0] Exit\n";
    cout << "\nSelect an option (0-4): ";
    
    int choice;
    cin >> choice;
    return choice;
}

// Forward declarations for all functions
void clearScreen();
int showMainMenu();
void takeQuiz();
vector<Question> loadQuestions();
void generateFromKeywords();
vector<Question> generateQuestions(const string& keyword, int count);
void addQuestion();

// Function to compare questions for finding duplicates
bool operator==(const Question& q1, const Question& q2) {
    return q1.question == q2.question && 
           q1.options == q2.options && 
           q1.correctOption == q2.correctOption;
}

void addQuestion() {
    // First, load existing questions
    vector<Question> existingQuestions = loadQuestions();
    
    // Get new question from user
    Question q;
    cout << "\n=== ADD NEW QUESTION ===\n\n";
    cout << "Enter the question: ";
    cin.ignore();
    getline(cin, q.question);
    
    // Validate if question already exists
    for (const auto& existingQ : existingQuestions) {
        if (existingQ.question == q.question) {
            cout << "\nError: This question already exists!\n";
            cout << "Press Enter to continue...";
            cin.ignore();
            return;
        }
    }
    
    cout << "Enter number of options (2-4): ";
    int numOptions;
    cin >> numOptions;
    
    if (numOptions < 2 || numOptions > 4) {
        cout << "Invalid number of options. Setting to 4.\n";
        numOptions = 4;
    }
    
    cin.ignore();
    for (int i = 0; i < numOptions; i++) {
        string option;
        cout << "Enter option " << (i + 1) << ": ";
        getline(cin, option);
        q.options.push_back(option);
    }
    
    cout << "Enter the correct option number (1-" << numOptions << "): ";
    cin >> q.correctOption;
    
    // Add to existing questions
    existingQuestions.push_back(q);
    
    // Save all questions back to file (overwrite)
    ofstream outFile("quiz_questions.txt", ios::trunc);  // Truncate existing content
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    
    for (const auto& question : existingQuestions) {
        outFile << question.question << "\n";
        outFile << question.options.size() << "\n";
        for (const auto& option : question.options) {
            outFile << option << "\n";
        }
        outFile << question.correctOption << "\n\n";
    }
    
    outFile.close();
    cout << "\nQuestion added successfully!\n";
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

vector<Question> loadQuestions() {
    vector<Question> questions;
    ifstream inFile("quiz_questions.txt");
    
    if (!inFile) {
        // If file doesn't exist, return empty vector
        return questions;
    }
    
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;  // Skip empty lines between questions
        
        Question q;
        q.question = line;
        
        // Read number of options
        if (!getline(inFile, line)) break;
        int numOptions;
        try {
            numOptions = stoi(line);
        } catch (...) {
            // If we can't read the number, skip this question
            continue;
        }
        
        // Read options
        for (int i = 0; i < numOptions; i++) {
            if (!getline(inFile, line)) break;
            q.options.push_back(line);
        }
        
        // Read correct option
        if (!getline(inFile, line)) break;
        try {
            q.correctOption = stoi(line);
        } catch (...) {
            // If we can't read the correct option, skip this question
            continue;
        }
        
        questions.push_back(q);
    }
    
    inFile.close();
    return questions;
}

void viewAllQuestions() {
    clearScreen();
    cout << "=== ALL QUESTIONS ===\n\n";
    
    for (const auto& category : questionBank) {
        cout << "\n--- " << category.first << " ---\n";
        int qNum = 1;
        for (const auto& question : category.second) {
            cout << "\n" << qNum++ << ". " << question.question << "\n";
            for (size_t i = 0; i < question.options.size(); i++) {
                cout << "   " << (i + 1) << ") " << question.options[i];
                if ((i + 1) == question.correctOption) cout << " (Correct)";
                cout << "\n";
            }
        }
    }
    
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void manageQuestions() {
    while (true) {
        clearScreen();
        cout << "=== MANAGE QUESTIONS ===\n\n";
        cout << "[1] View All Questions\n";
        cout << "[2] Add New Question\n";
        cout << "[3] Back to Main Menu\n";
        cout << "\nSelect an option (1-3): ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                viewAllQuestions();
                break;
            case 2:
                addQuestion();
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                cin.ignore();
                cin.get();
        }
    }
}

void viewStatistics() {
    clearScreen();
    cout << "=== QUIZ STATISTICS ===\n\n";
    
    // Count total questions in all categories
    int totalQuestions = 0;
    for (const auto& category : questionBank) {
        totalQuestions += category.second.size();
    }
    
    cout << "Total Categories: " << questionBank.size() << "\n";
    cout << "Total Questions: " << totalQuestions << "\n";
    cout << "\nQuestions by Category:\n";
    
    for (const auto& category : questionBank) {
        cout << "- " << category.first << ": " << category.second.size() << " questions\n";
    }
    
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void takeQuiz() {
    clearScreen();
    cout << "=== CREATE NEW QUIZ ===\n\n";
    
    // Ask for number of questions
    int numQuestions;
    cout << "Enter number of questions (1-20): ";
    cin >> numQuestions;
    numQuestions = max(1, min(20, numQuestions));
    
    // Load questions from both questionBank and quiz_questions.txt
    vector<Question> allQuestions;
    
    // Add questions from questionBank
    for (const auto& category : questionBank) {
        allQuestions.insert(allQuestions.end(), category.second.begin(), category.second.end());
    }
    
    // Add questions from file
    vector<Question> fileQuestions = loadQuestions();
    allQuestions.insert(allQuestions.end(), fileQuestions.begin(), fileQuestions.end());
    
    if (allQuestions.empty()) {
        cout << "No questions available. Please add questions first.\n";
        cin.ignore();
        cin.get();
        return;
    }
    
    // Shuffle questions
    srand(time(0));
    random_shuffle(allQuestions.begin(), allQuestions.end());
    
    // Take only the requested number of questions
    if (numQuestions > allQuestions.size()) {
        cout << "Only " << allQuestions.size() << " questions available. Using all.\n";
        numQuestions = allQuestions.size();
    } else {
        allQuestions.resize(numQuestions);
    }
    
    // Start the quiz
    int score = 0;
    cout << "\n--- Starting Quiz (" << numQuestions << " questions) ---\n\n";
    
    for (int i = 0; i < numQuestions; i++) {
        const Question& q = allQuestions[i];
        
        cout << "Question " << (i + 1) << ": " << q.question << "\n";
        for (size_t j = 0; j < q.options.size(); j++) {
            cout << "   " << (j + 1) << ". " << q.options[j] << "\n";
        }
        
        int answer;
        while (true) {
            cout << "\nYour answer (1-" << q.options.size() << "): ";
            cin >> answer;
            if (answer >= 1 && answer <= static_cast<int>(q.options.size())) {
                break;
            }
            cout << "Please enter a number between 1 and " << q.options.size() << ".\n";
        }
        
        if (answer == q.correctOption) {
            cout << "✓ Correct!\n\n";
            score++;
        } else {
            cout << "✗ Wrong! The correct answer was " << q.correctOption 
                 << ". " << q.options[q.correctOption - 1] << "\n\n";
        }
        
        // Pause between questions
        if (i < numQuestions - 1) {
            cout << "Press Enter for next question...";
            cin.ignore();
            cin.get();
        }
    }
    
    // Show results
    cout << "\n--- Quiz Complete! ---\n";
    cout << "Your score: " << score << "/" << numQuestions 
         << " (" << fixed << setprecision(1) << (score * 100.0 / numQuestions) << "%)\n";
    
    cout << "\nPress Enter to return to main menu...";
    cin.ignore();
    cin.get();
}

void showMenu() {
    while (true) {
        cout << "\n=== Quiz Generator ===\n";
        cout << "1. Add a Question\n";
        cout << "2. Take a Quiz\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                addQuestion();
                break;
            case 2:
                takeQuiz();
                break;
            case 3:
                cout << "Thank you for using Quiz Generator!\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        clearScreen();
    }
}

// Function to handle the Generate from Keywords feature
void generateFromKeywords() {
    clearScreen();
    cout << "=== GENERATE QUIZ FROM KEYWORDS ===\n\n";
    
    // Display available keywords
    cout << "Available keywords: ";
    bool first = true;
    for (const auto& category : questionBank) {
        if (!first) cout << ", ";
        cout << "'" << category.first << "'";
        first = false;
    }
    cout << "\n\n";
    
    string keyword;
    int numQuestions;
    
    cout << "Enter a keyword from the list above (e.g., 'science', 'history', 'programming'): ";
    cin.ignore();
    getline(cin, keyword);
    
    // Convert keyword to lowercase for case-insensitive comparison
    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);
    
    // Check if keyword exists
    bool keywordExists = false;
    for (const auto& category : questionBank) {
        string lowerCategory = category.first;
        transform(lowerCategory.begin(), lowerCategory.end(), lowerCategory.begin(), ::tolower);
        if (lowerCategory == lowerKeyword) {
            keywordExists = true;
            keyword = category.first; // Use the original case
            break;
        }
    }
    
    if (!keywordExists) {
        cout << "\nWarning: The keyword '" << keyword << "' doesn't match any category. "
             << "You can still proceed, but the quiz might be empty.\n";
    }
    
    cout << "\nEnter number of questions (1-20): ";
    cin >> numQuestions;
    numQuestions = max(1, min(20, numQuestions));  // Ensure between 1-20
    
    vector<Question> generatedQuestions = generateQuestions(keyword, numQuestions);
    
    if (generatedQuestions.empty()) {
        cout << "\nNo questions found for the given keyword.\n";
    } else {
        cout << "\n=== GENERATED QUIZ ===\n\n";
        int score = 0;
        
        for (size_t i = 0; i < generatedQuestions.size(); i++) {
            const Question& q = generatedQuestions[i];
            
            cout << "Question " << (i + 1) << ": " << q.question << "\n";
            for (size_t j = 0; j < q.options.size(); j++) {
                cout << "   " << (j + 1) << ". " << q.options[j] << "\n";
            }
            
            int answer;
            cout << "\nYour answer (1-" << q.options.size() << "): ";
            cin >> answer;
            
            if (answer == q.correctOption) {
                cout << "✓ Correct!\n\n";
                score++;
            } else {
                cout << "✗ Wrong! The correct answer was " << q.correctOption 
                     << ". " << q.options[q.correctOption - 1] << "\n\n";
            }
        }
        
        cout << "\n=== QUIZ COMPLETE! ===\n";
        cout << "Your score: " << score << "/" << generatedQuestions.size() 
             << " (" << (score * 100.0 / generatedQuestions.size()) << "%)\n";
    }
    
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

int main() {
    // Set up console for better display
    system("title Quiz Generator");
    system("color 0A");  // Black background with green text
    
    while (true) {
        clearScreen();
        cout << "\n=== QUIZ GENERATOR MAIN MENU ===\n\n";
        cout << "[1] Create New Quiz\n";
        cout << "[2] Generate from Keywords\n";
        cout << "[3] Manage Questions\n";
        cout << "[4] View Statistics\n";
        cout << "[0] Exit\n";
        cout << "\nSelect an option (0-4): ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 0: // Exit
                cout << "\nThank you for using Quiz Generator!\n";
                return 0;
                
            case 1: // Create New Quiz
                takeQuiz();
                break;
                
            case 2: // Generate from Keywords
                generateFromKeywords();
                break;
                
            case 3: // Manage Questions
                manageQuestions();
                break;
                
            case 4: // View Statistics
                // Add your statistics code here
                cout << "\nStatistics feature coming soon!\n";
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
                
            default:
                cout << "\nInvalid choice. Please try again.\n";
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
        }
    }
    
    return 0;
}
