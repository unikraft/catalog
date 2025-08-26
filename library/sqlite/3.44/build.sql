-- Drop tables if they exist
DROP TABLE IF EXISTS OrderDetail;
DROP TABLE IF EXISTS [Order];
DROP TABLE IF EXISTS Product;
DROP TABLE IF EXISTS Customer;

-- Create Customer table
CREATE TABLE Customer (
    CustomerID INTEGER NOT NULL PRIMARY KEY,
    Name TEXT NOT NULL,
    Email TEXT
);

-- Create Product table
CREATE TABLE Product (
    ProductID INTEGER NOT NULL PRIMARY KEY,
    ProductName TEXT NOT NULL,
    Price REAL NOT NULL
);

-- Create Order table
CREATE TABLE [Order] (
    OrderID INTEGER NOT NULL PRIMARY KEY,
    CustomerID INTEGER NOT NULL,
    OrderDate TEXT NOT NULL,
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID)
);

-- Create OrderDetail table
CREATE TABLE OrderDetail (
    OrderDetailID INTEGER NOT NULL PRIMARY KEY,
    OrderID INTEGER NOT NULL,
    ProductID INTEGER NOT NULL,
    Quantity INTEGER NOT NULL,
    FOREIGN KEY (OrderID) REFERENCES [Order](OrderID),
    FOREIGN KEY (ProductID) REFERENCES Product(ProductID)
);

-- Populate Customer table
INSERT INTO Customer (CustomerID, Name, Email) VALUES (1, 'Alice Smith', 'alice@example.com');
INSERT INTO Customer (CustomerID, Name, Email) VALUES (2, 'Bob Johnson', 'bob@example.com');

-- Populate Product table
INSERT INTO Product (ProductID, ProductName, Price) VALUES (1, 'Laptop', 999.99);
INSERT INTO Product (ProductID, ProductName, Price) VALUES (2, 'Smartphone', 499.99);
INSERT INTO Product (ProductID, ProductName, Price) VALUES (3, 'Headphones', 89.99);

-- Populate Order table
INSERT INTO [Order] (OrderID, CustomerID, OrderDate) VALUES (1, 1, '2025-03-20');
INSERT INTO [Order] (OrderID, CustomerID, OrderDate) VALUES (2, 2, '2025-03-21');

-- Populate OrderDetail table
INSERT INTO OrderDetail (OrderDetailID, OrderID, ProductID, Quantity) VALUES (1, 1, 1, 1);
INSERT INTO OrderDetail (OrderDetailID, OrderID, ProductID, Quantity) VALUES (2, 1, 3, 2);
INSERT INTO OrderDetail (OrderDetailID, OrderID, ProductID, Quantity) VALUES (3, 2, 2, 1);
