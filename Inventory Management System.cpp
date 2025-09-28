//Group NIGANG
//Alecs Louis Murillon
//Caille Louis F. Aquino
//Cezar Soriano
//Christian Vasquez
//Francois Padulina Osea
//Jeward Oliva
//Mark Arvie Ampongan


// NOTE:
// 1. MAXIMIZE CMD WINDOW
// 2. SCROLL OUT FOR COMPLETE DESIGN

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits> // Required for numeric_limits

#ifdef _WIN32
#include <windows.h> // For Windows-specific color functions
#endif

using namespace std;

// --- Color Codes ---
// ANSI escape codes (for terminals that support them)
#define ANSI_RESET   "\033[0m"
#define ANSI_BLACK   "\033[30m"
#define ANSI_RED     "\033[31m"
#define ANSI_GREEN   "\033[32m"
#define ANSI_YELLOW  "\033[33m"
#define ANSI_BLUE    "\033[34m"
#define ANSI_MAGENTA "\033[35m"
#define ANSI_CYAN    "\033[36m"
#define ANSI_WHITE   "\033[37m"

// Windows console color codes (using <windows.h>)
#ifdef _WIN32
enum ConsoleColor {
    BLACK = 0,
    DARK_BLUE = 1,
    DARK_GREEN = 2,
    DARK_CYAN = 3,
    DARK_RED = 4,
    DARK_MAGENTA = 5,
    DARK_YELLOW = 6,
    GRAY = 7,
    DARK_GRAY = 8,
    BLUE = 9,
    GREEN = 10,
    CYAN = 11,
    RED = 12,
    MAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};
#endif

// Product structure to hold inventory data
struct Product {
    int SKU;
    string name;
    double price;
    int quantity;
};

// Global inventory array
vector<Product> inventory;

// Function declarations
void displayInventory();
void addProduct();
void editProduct();
void searchProduct();
void deleteProduct();
void sortInventoryBySKU();
void sortInventoryByPrice();
int binarySearch(int SKU);
void printCentered(const string& text, int color = -1);
void printLine(char symbol, int length);
void printLineNoEn(char symbol, int length);
void setColor(int color);
void resetColor();
double getDoubleInput(const string& prompt);
int getIntInput(const string& prompt);
void printAsciiTitle(const string& title);

int main() {
    char choice;
    do {
        system("cls"); // Clear the screen

        // --- Aesthetic Menu ---
        printAsciiTitle("INVENTORY MANAGEMENT SYSTEM"); // Main title 

        cout << "\n";
        setColor(CYAN);
        printLineNoEn(' ', 57); cout<<"+"; printLineNoEn('-', 40); cout<<"+\n";
        resetColor();
        
        printLineNoEn(' ', 57); setColor(CYAN); cout << "|"; printLineNoEn(' ', 40); cout << "|\n";
        printLineNoEn(' ', 57); setColor(CYAN); cout << "|"; printLineNoEn(' ', 14); cout << ANSI_RESET << "Choose Action"; setColor(CYAN); printLineNoEn(' ', 13); cout << "|\n";
        printLineNoEn(' ', 57); setColor(CYAN); cout << "|"; printLineNoEn(' ', 40); cout << "|\n";
        printLineNoEn(' ', 57); setColor(CYAN); cout << "|" << ANSI_RESET << "\t" << ANSI_YELLOW << "1." << ANSI_RESET << " Display Inventory"; setColor(CYAN); printLineNoEn(' ', 14); cout << "|\n";
        printLineNoEn(' ', 57); setColor(CYAN); cout << "|" << ANSI_RESET << "\t" << ANSI_YELLOW << "2." << ANSI_RESET << " Add Product"; setColor(CYAN); printLineNoEn(' ', 20); cout << "|\n";
        printLineNoEn(' ', 57); setColor(CYAN); cout << "|" << ANSI_RESET << "\t" << ANSI_YELLOW << "3." << ANSI_RESET << " Edit Product"; setColor(CYAN); printLineNoEn(' ', 19); cout << "|\n";
        printLineNoEn(' ', 57); setColor(CYAN); cout << "|" << ANSI_RESET << "\t" << ANSI_YELLOW << "4." << ANSI_RESET << " Search Product"; setColor(CYAN); printLineNoEn(' ', 17); cout << "|\n";
        printLineNoEn(' ', 57); setColor(CYAN); cout << "|" << ANSI_RESET << "\t" << ANSI_YELLOW << "5." << ANSI_RESET << " Delete Product"; setColor(CYAN); printLineNoEn(' ', 17); cout << "|\n";
        printLineNoEn(' ', 57); setColor(CYAN); cout << "|" << ANSI_RESET << "\t" << ANSI_YELLOW << "6." << ANSI_RESET << " Sort Inventory by SKU"; setColor(CYAN); printLineNoEn(' ', 10); cout << "|\n";
        printLineNoEn(' ', 57); setColor(CYAN); cout << "|" << ANSI_RESET << "\t" << ANSI_YELLOW << "7." << ANSI_RESET << " Sort Inventory by Price"; setColor(CYAN); printLineNoEn(' ', 8); cout << "|\n";
        printLineNoEn(' ', 57); setColor(CYAN); cout << "|" << ANSI_RESET << "\t" << ANSI_YELLOW << "8." << ANSI_RESET << " Exit"; setColor(CYAN); printLineNoEn(' ', 27); cout << "|\n";
        printLineNoEn(' ', 57); setColor(CYAN); cout << "|"; printLineNoEn(' ', 40); cout << "|\n";

        setColor(CYAN); 
		printLineNoEn(' ', 57); cout<<"+"; printLineNoEn('-', 40); cout<<"+\n\n\n";
        resetColor();
        printLineNoEn(' ', 23); cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1': displayInventory(); break;
        case '2': addProduct(); break;
        case '3': editProduct(); break;
        case '4': searchProduct(); break;
        case '5': deleteProduct(); break;
        case '6': sortInventoryBySKU(); break;
        case '7': sortInventoryByPrice(); break;
        case '8':
            printAsciiTitle("Exiting...");
            break;
        default:
            setColor(RED);
            cout << "\n\n\n"; printLineNoEn(' ', 60); cout << ">>   Invalid option. Try again.   <<\n";
            resetColor();
            system("pause"); 
        }
    } while (choice != '8');

    return 0;
}

// Function to display inventory
void displayInventory() {
    system("cls");
    printAsciiTitle("CURRENT INVENTORY");
    cout << "\n";

    if (inventory.empty()) {
    	setColor(RED);
    	cout << "\n\n\n"; printLineNoEn(' ', 58); cout << ">>   Inventory is empty.   <<";
    	resetColor();
    } else {
        setColor(GREEN);
        cout << "\n";
        printLineNoEn(' ', 33); cout << left << setw(20) << "SKU" << setw(30) << "Name" << setw(15) << "Price" << setw(15) << "Quantity" << endl;
        printLineNoEn(' ', 33); printLine('-', 80);
        resetColor();
        for (const auto& product : inventory) {
            printLineNoEn(' ', 33);
			cout << setw(20) << product.SKU
                 << setw(30) << product.name
                 << setw(15) << fixed << setprecision(2) << product.price
                 << setw(15) << product.quantity << endl;
        }
    }

    cout << "\n";
    system("pause");
}

// Function to add a product
void addProduct() {
    system("cls");
    Product newProduct;
    printAsciiTitle("ADD PRODUCT");
	
    cout << "\n\n"; printLineNoEn(' ', 23); newProduct.SKU = getIntInput("Enter SKU: ");

    if (binarySearch(newProduct.SKU) != -1) {
        setColor(RED);
        cout << "\n\n"; printLineNoEn(' ', 50); cout << ">>   Error: Product with this SKU already exists.   <<\n";
        resetColor();
        system("pause");
        return;
    }

    printLineNoEn(' ', 23); cout << "Enter Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newProduct.name);
    printLineNoEn(' ', 23); newProduct.price = getDoubleInput("Enter Price: ");
    printLineNoEn(' ', 23); newProduct.quantity = getIntInput("Enter Quantity: ");

    inventory.push_back(newProduct);
    setColor(GREEN);
    cout << "\n\n"; printLineNoEn(' ', 59); cout << ">>   Product added successfully.   <<\n";
    resetColor();
    system("pause");
}

// Function to edit a product
void editProduct() {
    system("cls");
    string sSKU;
    int nSKU;
    printAsciiTitle("EDIT PRODUCT");

    cout << "\n"; printLineNoEn(' ', 23); cout << "Enter SKU of the product to edit: ";
    cin >> sSKU;
    
    // For error handling. incase the user inputs non-numeric characters
    try { nSKU = stoi(sSKU); } catch (const std::invalid_argument& e) {}

    int index = binarySearch(nSKU);
    if (index != -1) {
        cout << "\n"; printLineNoEn(' ', 23); cout << "Editing product: " << inventory[index].name << endl;
        setColor(GREEN);
        printLineNoEn(' ', 23);
        printLine('-', 50);
        resetColor();
        printLineNoEn(' ', 23); cout << "Enter new Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, inventory[index].name);

        printLineNoEn(' ', 23); inventory[index].price = getDoubleInput("Enter new Price: ");
        printLineNoEn(' ', 23); inventory[index].quantity = getIntInput("Enter new Quantity: ");

        setColor(GREEN);
        cout << "\n\n"; printLineNoEn(' ', 23); cout << "Product updated successfully.\n";
        resetColor();
    } else {
        setColor(RED);
        cout << "\n\n\n"; printLineNoEn(' ', 65); cout << ">>   Product not found.   <<\n";
        resetColor();
    }
    system("pause");
}

// Function to search for a product
void searchProduct() {
    system("cls");
    string sSKU;
    int nSKU;
    printAsciiTitle("SEARCH PRODUCT");

    cout << "\n"; printLineNoEn(' ', 23); cout << "Enter SKU to search: ";
    cin >> sSKU;
    
    // For error handling. incase the user inputs non-numeric characters
    try { nSKU = stoi(sSKU); } catch (const std::invalid_argument& e) {}

    int index = binarySearch(nSKU);
    if (index != -1) {
        cout << "\n";
        setColor(GREEN);
        printLineNoEn(' ', 53); printLine('-', 50);
        printLineNoEn(' ', 73); cout << "Product found\n";
        printLineNoEn(' ', 53); printLine('-', 50);
        resetColor();
        printLineNoEn(' ', 53); cout << "SKU       "; setColor(GREEN); cout << "|  "; resetColor(); cout << inventory[index].SKU << endl;
        printLineNoEn(' ', 53); cout << "Name      "; setColor(GREEN); cout << "|  "; resetColor(); cout << inventory[index].name << endl;
        printLineNoEn(' ', 53); cout << "Price     "; setColor(GREEN); cout << "|  "; resetColor(); cout << fixed << setprecision(2) << inventory[index].price << endl;
        printLineNoEn(' ', 53); cout << "Quantity  "; setColor(GREEN); cout << "|  "; resetColor(); cout << inventory[index].quantity << endl;
    } else {
        setColor(RED);
        cout << "\n\n\n"; printLineNoEn(' ', 63); cout << ">>   Product not found.   <<\n";
        resetColor();
    }
    system("pause");
}

// Function to delete a product
void deleteProduct() {
    system("cls");
    string sSKU;
    int nSKU;
    printAsciiTitle("DELETE PRODUCT");
    
    cout << "\n\n"; printLineNoEn(' ', 23); cout << "Enter SKU to delete: ";
    cin >> sSKU;
    
    // For error handling. incase the user inputs non-numeric characters
    try { nSKU = stoi(sSKU); } catch (const std::invalid_argument& e) {}

    int index = binarySearch(nSKU);
    if (index != -1) {
        cout << "\n"; printLineNoEn(' ', 23); cout << "Are you sure you want to delete " << inventory[index].name << "? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            inventory.erase(inventory.begin() + index);
            setColor(GREEN);
            cout << "\n\n"; printLineNoEn(' ', 23); cout << "Product deleted successfully.\n";
            resetColor();
        } else {
            setColor(RED);
            cout << "\n\n"; printLineNoEn(' ', 23); cout << "Deletion cancelled.\n";
            resetColor();
        }
    } else {
        setColor(RED);
        cout << "\n\n\n"; printLineNoEn(' ', 63); cout << ">>   Product not found.   <<\n";
        resetColor();
    }
    system("pause");
}

// Function to sort inventory by SKU
void sortInventoryBySKU() {
    sort(inventory.begin(), inventory.end(), [](const Product& a, const Product& b) {
        return a.SKU < b.SKU;
    });
    setColor(GREEN);
    cout << "\n\n"; printLineNoEn(' ', 23); cout << "Inventory sorted by SKU.\n";
    resetColor();
    system("pause");
}

// Function to sort inventory by price
void sortInventoryByPrice() {
    sort(inventory.begin(), inventory.end(), [](const Product& a, const Product& b) {
        return a.price < b.price;
    });
    setColor(GREEN);
    cout << "\n\n"; printLineNoEn(' ', 23); cout << "Inventory sorted by price.\n";
    resetColor();
    system("pause");
}

// Binary search for a product by SKU
int binarySearch(int SKU) {
    int left = 0, right = inventory.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (inventory[mid].SKU == SKU) {
            return mid;
        } else if (inventory[mid].SKU < SKU) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Helper function to print centered text (with optional color)
void printCentered(const string& text, int color) {
    if (color != -1) {
        setColor(color);
    }
    int padding = (50 - text.length()) / 2;
    cout << setw(padding + text.length()) << text << endl;
    if (color != -1) {
        resetColor();
    }
}

// Helper function to print a line of characters
void printLine(char symbol, int length) {
    cout << setfill(symbol) << setw(length) << "" << setfill(' ') << endl;
}

// Helper function to print a line of characters w/ endl
void printLineNoEn(char symbol, int length) {
    cout << setfill(symbol) << setw(length) << "" << setfill(' ');
}

// --- Color Functions ---

// Set text color (Windows)
#ifdef _WIN32
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#else
// Set text color (ANSI escape codes - for Linux/macOS/other terminals)
void setColor(int color) {
    switch (color) {
    case BLACK:     cout << ANSI_BLACK; break;
    case RED:       cout << ANSI_RED; break;
    case GREEN:     cout << ANSI_GREEN; break;
    case YELLOW:    cout << ANSI_YELLOW; break;
    case BLUE:      cout << ANSI_BLUE; break;
    case MAGENTA:   cout << ANSI_MAGENTA; break;
    case CYAN:      cout << ANSI_CYAN; break;
    case WHITE:     cout << ANSI_WHITE; break;
    default:        cout << ANSI_RESET; break; // Reset to default
    }
}
#endif

// Reset text color to default
void resetColor() {
#ifdef _WIN32
    setColor(WHITE); // Set to white (default) on Windows
#else
    cout << ANSI_RESET;
#endif
}

// --- Input Validation Functions ---

// Function to get valid double input
double getDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            // Input is a valid number
            if (value >= 0) {
                break; // Valid input, exit loop
            } else {
                setColor(RED);
                printLineNoEn(' ', 23); cout << "Please enter a non-negative value.\n\n";
                printLineNoEn(' ', 23);
                resetColor();
            }
        } else {
            // Input is not a number
            setColor(RED);
            printLineNoEn(' ', 23); cout << "Invalid input. Please enter a numeric value.\n\n";
            printLineNoEn(' ', 23);
            resetColor();
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    return value;
}

int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            // Input is a valid number
            if (value >= 0) {
                break; // Valid input, exit loop
            } else {
                setColor(RED);
                printLineNoEn(' ', 23); cout << "Please enter a non-negative value.\n\n";
                printLineNoEn(' ', 23);
                resetColor();
            }
        } else {
            // Input is not a number
            setColor(RED);
            printLineNoEn(' ', 23); cout << "Invalid input. Please enter a numeric value.\n\n";
            printLineNoEn(' ', 23);
            resetColor();
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    return value;
}

void printAsciiTitle(const string& title) {

    if (title == "INVENTORY MANAGEMENT SYSTEM") {
        setColor(CYAN);
        cout << R"(
 _____ _____ _____ _____ _____ _____ _____ _____ __ __    _____ _____ _____ _____ _____ _____ _____ _____ _____ _____    _____ __ __ _____ _____ _____ _____ 
|     |   | |  |  |   __|   | |_   _|     | __  |  |  |  |     |  _  |   | |  _  |   __|   __|     |   __|   | |_   _|  |   __|  |  |   __|_   _|   __|     |
|-   -| | | |  |  |   __| | | | | | |  |  |    -|_   _|  | | | |     | | | |     |  |  |   __| | | |   __| | | | | |    |__   |_   _|__   | | | |   __| | | |
|_____|_|___|\___/|_____|_|___| |_| |_____|__|__| |_|    |_|_|_|__|__|_|___|__|__|_____|_____|_|_|_|_____|_|___| |_|    |_____| |_| |_____| |_| |_____|_|_|_|
                                                                                                                                                             
)" << '\n';
        resetColor();
    }
    else if (title == "CURRENT INVENTORY")
    {
        setColor(YELLOW);
        cout << R"(
                        _____ _____ _____ _____ _____ _____ _____    _____ _____ _____ _____ _____ _____ _____ _____ __ __ 
                       |     |  |  | __  | __  |   __|   | |_   _|  |     |   | |  |  |   __|   | |_   _|     | __  |  |  |
                       |   --|  |  |    -|    -|   __| | | | | |    |-   -| | | |  |  |   __| | | | | | |  |  |    -|_   _|
                       |_____|_____|__|__|__|__|_____|_|___| |_|    |_____|_|___|\___/|_____|_|___| |_| |_____|__|__| |_|  
)" << "\n";
        resetColor();
    }

    else if (title == "ADD PRODUCT") {
        setColor(YELLOW);
        cout << R"(
                                               _____ ____  ____     _____ _____ _____ ____  _____ _____ _____ 
                                              |  _  |    \|    \   |  _  | __  |     |    \|  |  |     |_   _|
                                              |     |  |  |  |  |  |   __|    -|  |  |  |  |  |  |   --| | |  
                                              |__|__|____/|____/   |__|  |__|__|_____|____/|_____|_____| |_|  
)" << "\n";
        resetColor();
    } else if (title == "EDIT PRODUCT") {
        setColor(YELLOW);
        cout << R"(
                                            _____ ____  _____ _____    _____ _____ _____ ____  _____ _____ _____ 
                                           |   __|    \|     |_   _|  |  _  | __  |     |    \|  |  |     |_   _|
                                           |   __|  |  |-   -| | |    |   __|    -|  |  |  |  |  |  |   --| | |  
                                           |_____|____/|_____| |_|    |__|  |__|__|_____|____/|_____|_____| |_|  
                                
)" << "\n";
        resetColor();
    } else if (title == "SEARCH PRODUCT") {
        setColor(YELLOW);
        cout << R"(
                                      _____ _____ _____ _____ _____ _____    _____ _____ _____ ____  _____ _____ _____ 
                                     |   __|   __|  _  | __  |     |  |  |  |  _  | __  |     |    \|  |  |     |_   _|
                                     |__   |   __|     |    -|   --|     |  |   __|    -|  |  |  |  |  |  |   --| | |  
                                     |_____|_____|__|__|__|__|_____|__|__|  |__|  |__|__|_____|____/|_____|_____| |_|  
                                                                                  
)" << "\n";
        resetColor();
    }
    else if (title == "DELETE PRODUCT")
    {
        setColor(YELLOW);
        cout << R"(
                                      ____  _____ __    _____ _____ _____    _____ _____ _____ ____  _____ _____ _____ 
                                     |    \|   __|  |  |   __|_   _|   __|  |  _  | __  |     |    \|  |  |     |_   _|
                                     |  |  |   __|  |__|   __| | | |   __|  |   __|    -|  |  |  |  |  |  |   --| | |  
                                     |____/|_____|_____|_____| |_| |_____|  |__|  |__|__|_____|____/|_____|_____| |_|  
                                
)" << "\n";
        resetColor();
    }
    
    else if (title == "Exiting...") {
        setColor(MAGENTA);
        cout << R"(
                                                               _____     _ _   _               
                                                              |   __|_ _|_| |_|_|___ ___       
                                                              |   __|_'_| |  _| |   | . |_ _ _ 
                                                              |_____|_,_|_|_| |_|_|_|_  |_|_|_|
                                                                                    |___|      
                        
)" << "\n";
        resetColor();
    }
}