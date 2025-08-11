#include <iostream>
#include <fstream>
using namespace std;

class Product {
private:
    int productID;
    char productName[50];
    double productPrice;
    int quantity;

public:
    Product() {
        productID = 0;
        productPrice = 0.0;
        quantity = 0;
        productName[0] = '\0';
    }

    Product(int id, const char name[], double price, int qty) {
        productID = id;
        productPrice = price;
        quantity = qty;
        int i = 0;
        while (name[i] != '\0' && i < 49) {
            productName[i] = name[i];
            i++;
        }
        productName[i] = '\0';
    }

    int getID() const {
        return productID;
    }

    const char* getName() const {
        return productName;
    }

    double getPrice() const {
        return productPrice;
    }

    int getQuantity() const {
        return quantity;
    }

    void displayProduct() const {
        cout << "Product Name: " << productName
             << ", Quantity: " << quantity
             << ", Price: Rs." << productPrice
             << ", Total: Rs." << productPrice * quantity << endl;
    }
};

class Customer {
private:
    int customerID;
    char customerName[50];
    Product cart[10];
    int cartSize;

public:
    Customer() {
        customerID = 0;
        cartSize = 0;
        customerName[0] = '\0';
    }

    Customer(int id, const char name[]) {
        customerID = id;
        cartSize = 0;
        int i = 0;
        while (name[i] != '\0' && i < 49) {
            customerName[i] = name[i];
            i++;
        }
        customerName[i] = '\0';
    }

    int getID() const {
        return customerID;
    }

    const char* getName() const {
        return customerName;
    }

    void addProductToCart(const Product& product) {
        if (cartSize < 10) {
            cart[cartSize++] = product;
            cout << "Product added to cart.\n";
        } else {
            cout << "Cart is full!\n";
        }
    }

    void removeProductFromCart(int productID) {
        bool found = false;
        for (int i = 0; i < cartSize; i++) {
            if (cart[i].getID() == productID) {
                for (int j = i; j < cartSize - 1; j++) {
                    cart[j] = cart[j + 1];
                }
                cartSize--;
                found = true;
                cout << "Product removed from cart.\n";
                break;
            }
        }
        if (!found) {
            cout << "Product not found in cart.\n";
        }
    }

    void displayCart() const {
        if (cartSize == 0) {
            cout << "Cart is empty.\n";
            return;
        }

        cout << "Customer: " << customerName << "'s Cart:\n";
        for (int i = 0; i < cartSize; i++) {
            cart[i].displayProduct();
        }
    }

    const Product* getCart() const {
        return cart;
    }

    int getCartSize() const {
        return cartSize;
    }
};

class Order {
private:
    int orderID;
    Customer customer;
    Product productList[10];
    int productListSize;
    double totalAmount;

public:
    Order(int id, const Customer& cust)
        : orderID(id), customer(cust), productListSize(0), totalAmount(0.0) {
        int size = cust.getCartSize();
        const Product* cart = cust.getCart();
        for (int i = 0; i < size; i++) {
            productList[i] = cart[i];
            productListSize++;
            totalAmount += cart[i].getPrice() * cart[i].getQuantity();
        }
    }

    void displayOrder() const {
        cout << "\n--- Order Summary ---\n";
        cout << "Order ID: " << orderID << endl;
        customer.displayCart();
        cout << "Total Amount: Rs." << totalAmount << endl;
    }

    void saveOrderToCSV() const {
        ifstream inFile("cart_details.csv");
        bool isEmpty = inFile.peek() == ifstream::traits_type::eof();
        inFile.close();

        ofstream file("cart_details.csv", ios::app);
        if (isEmpty) {
            file << "Customer_ID,Customer_Name,Cart_Size,Total_Amount\n";
        }

        file << customer.getID() << "," << customer.getName() << ","
             << productListSize << "," << totalAmount << "\n";
        file.close();
    }
};

// MAIN FUNCTION
int main() {
    int customerID;
    char customerName[50];

    cout << "Enter Customer ID: ";
    cin >> customerID;
    cin.ignore();

    cout << "Enter Customer Name: ";
    cin.getline(customerName, 50);

    Customer customer(customerID, customerName);
    bool running = true;

    while (running) {
        int choice;
        cout << "\n1. Add Product to Cart\n2. Remove Product from Cart\n3. View Cart\n4. Checkout\n5. Exit\nChoose an option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            int productID, quantity;
            char productName[50];
            double productPrice;

            cout << "Enter Product ID: ";
            cin >> productID;
            cin.ignore();

            cout << "Enter Product Name: ";
            cin.getline(productName, 50);

            cout << "Enter Product Price: ";
            cin >> productPrice;

            cout << "Enter Quantity: ";
            cin >> quantity;

            if (productPrice <= 0 || quantity <= 0) {
                cout << "Invalid input!\n";
                break;
            }

            Product product(productID, productName, productPrice, quantity);
            customer.addProductToCart(product);
            break;
        }

        case 2: {
            int productID;
            cout << "Enter Product ID to remove: ";
            cin >> productID;
            customer.removeProductFromCart(productID);
            break;
        }

        case 3:
            customer.displayCart();
            break;

        case 4: {
            Order order(1, customer);
            order.displayOrder();
            order.saveOrderToCSV();
            cout << "Order saved to 'cart_details.csv'.\n";
            running = false;
            break;
        }

        case 5:
            cout << "Exiting. Thank you!\n";
            running = false;
            break;

        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}