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
    Product() : productID(0), productPrice(0.0), quantity(0) {
        productName[0] = '\0';
    }
    Product(int id, const char* name, double price, int qty)
        : productID(id), productPrice(price), quantity(qty) {
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
    void setQuantity(int qty) {
        quantity = qty;
    }
    void displayProduct() const {
        cout << "Product Name: " << productName << ", Quantity: " << quantity << ", Price: " << productPrice << endl;
    }
};
class Customer {
private:
    int customerID;
    char customerName[50];
    Product cart[10];
    int cartSize;
public:
    Customer(int id, const char* name) {
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
        } else {
            cout << "Cart is full!" << endl;
        }
    }
    void removeProductFromCart(int productID) {
        for (int i = 0; i < cartSize; ++i) {
            if (cart[i].getID() == productID) {
                for (int j = i; j < cartSize - 1; ++j) {
                    cart[j] = cart[j + 1];
                }
                cartSize--;
                break;
            }
        }
    }
    void displayCart() const {
        cout << "Customer: " << customerName << "'s Cart:" << endl;
        for (int i = 0; i < cartSize; ++i) {
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
        for (int i = 0; i < cust.getCartSize(); ++i) {
            productList[i] = cust.getCart()[i];
            productListSize++;
            totalAmount += productList[i].getPrice() * productList[i].getQuantity();
        }
    }
    double getTotalAmount() const {
        return totalAmount;
    }
    void displayOrder() const {
        cout << "Order ID: " << orderID << endl;
        customer.displayCart();
        cout << "Total Amount: " << totalAmount << endl;
    }
    void saveOrderToCSV() const {
        ifstream inFile("cart_details.csv");
        bool headersExist = false;
        string line;
        if (getline(inFile, line)) {
            headersExist = true;
        }
        inFile.close();
        ofstream file("cart_details.csv", ios::app);
        if (!headersExist) {
            file << "Customer_ID,Customer_Name,cart_size,total_Amount\n";
        }
        file << customer.getID() << "," << customer.getName() << "," << productListSize << "," << totalAmount << endl;
        file.close();
    }
};
int main() {
    system("cls");
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
        switch (choice) {
            case 1: {
                int productID;
                char productName[50];
                double productPrice;
                int quantity;
                cout << "Enter Product ID: ";
                cin >> productID;
                cin.ignore();
                cout << "Enter Product Name: ";
                cin.getline(productName, 50);
                cout << "Enter Product Price: ";
                cin >> productPrice;
                cout << "Enter Product Quantity: ";
                cin >> quantity;
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
            case 3: {
                customer.displayCart();
                break;
            }
            case 4: {
                Order order(1, customer);
                order.displayOrder();
                order.saveOrderToCSV();
                running = false;
                break;
            }
            case 5: {
                cout << "User has exited the cart." << endl;
                running = false;
                break;
            }
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
    return 0;
}