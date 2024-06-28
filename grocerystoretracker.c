#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_PRODUCTS 100
#define MAX_CUSTOMERS 50
#define MAX_ORDERS 100

// Struct definitions
typedef struct {
    int productId;
    char name[50];
    float price;
    int quantity;
} Product;

typedef struct {
    int customerId;
    char name[50];
    char address[100];
} Customer;

typedef struct {
    int orderId;
    Customer customer;
    Product products[MAX_PRODUCTS];
    int numProducts;
    float totalAmount;
    int isDelivered;
} Order;

typedef struct {
    Product products[MAX_PRODUCTS];
    int numProducts;
} GroceryStore;

// Function prototypes
void browseProducts(GroceryStore *store);
void placeOrder(GroceryStore *store, Customer *customer, Product *products, int numProducts);
void manageDeliveries(Order *orders, int numOrders);

// Global variables
GroceryStore store;
Customer customers[MAX_CUSTOMERS];
Order orders[MAX_ORDERS];
int numCustomers = 0;
int numOrders = 0;

int main() {
    // Initialize grocery store with some products
    store.numProducts = 0;
    strcpy(store.products[store.numProducts].name, "Milk");
    store.products[store.numProducts].price = 2.5;
    store.products[store.numProducts].quantity = 100;
    store.numProducts++;
    
    strcpy(store.products[store.numProducts].name, "Bread");
    store.products[store.numProducts].price = 1.5;
    store.products[store.numProducts].quantity = 200;
    store.numProducts++;

    // Example usage
    Customer customer1 = { 1, "Alice", "123 Main St" };
    customers[numCustomers++] = customer1;

    browseProducts(&store);

    Product orderProducts[MAX_PRODUCTS];
    orderProducts[0] = store.products[0]; // Order Milk
    placeOrder(&store, &customer1, orderProducts, 1);

    manageDeliveries(orders, numOrders);

    return 0;
}

// Function definitions

void browseProducts(GroceryStore *store) {
    printf("Available Products:\n");
    for (int i = 0; i < store->numProducts; ++i) {
        printf("Product ID: %d, Name: %s, Price: $%.2f, Quantity: %d\n", 
               store->products[i].productId, store->products[i].name, 
               store->products[i].price, store->products[i].quantity);
    }
    printf("\n");
}

void placeOrder(GroceryStore *store, Customer *customer, Product *products, int numProducts) {
    Order newOrder;
    newOrder.orderId = numOrders++; // Unique order ID
    newOrder.customer = *customer;
    newOrder.numProducts = numProducts;
    newOrder.totalAmount = 0.0;
    newOrder.isDelivered = 0;

    for (int i = 0; i < numProducts; ++i) {
        newOrder.products[i] = products[i];
        newOrder.totalAmount += products[i].price;
        // Update store inventory
        for (int j = 0; j < store->numProducts; ++j) {
            if (store->products[j].productId == products[i].productId) {
                store->products[j].quantity -= 1; // Assuming one unit per order for simplicity
                break;
            }
        }
    }

    orders[numOrders - 1] = newOrder;

    printf("Order placed successfully for Customer %s. Order ID: %d\n", customer->name, newOrder.orderId);
}

void manageDeliveries(Order *orders, int numOrders) {
    printf("\nManaging Deliveries:\n");
    for (int i = 0; i < numOrders; ++i) {
        if (!orders[i].isDelivered) {
            printf("Processing delivery for Order ID %d to %s.\n", orders[i].orderId, orders[i].customer.address);
            orders[i].isDelivered = 1; // Mark order as delivered
        }
    }
}
