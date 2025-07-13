.headers on
.mode column

-- List all customers
SELECT * FROM Customer;

-- List orders with customer names and order dates
SELECT O.OrderID, C.Name AS Customer, O.OrderDate
FROM [Order] O
JOIN Customer C ON O.CustomerID = C.CustomerID;

-- List order details with product names, quantities, and prices
SELECT O.OrderID, C.Name AS Customer, P.ProductName, OD.Quantity, P.Price
FROM OrderDetail OD
JOIN [Order] O ON OD.OrderID = O.OrderID
JOIN Customer C ON O.CustomerID = C.CustomerID
JOIN Product P ON OD.ProductID = P.ProductID;
