# payment-application
This Payment Application is a comprehensive project developed to handle various payment processing functions. It is structured into several modules, each responsible for specific functionalities:

## Project Structure
Application Module

### app.c and app.h
Manages the overall application logic.
Card Module

### card.c and card.h
Handles card-related operations such as capturing cardholder name, card expiration date, and card PAN (Primary Account Number).
Terminal Module

### terminal.c and terminal.h
Manages terminal operations, including transaction date, transaction amount, and maximum allowable amount.
Server Module

### server.c and server.h
Manages server-side operations, including transaction validation, account verification, and balance checking.
## Key Features
### Card Module

Functions to get cardholder name, card expiry date, and card PAN.
Error handling for invalid input data.
### Terminal Module

Functions to get transaction date and amount.
Functions to check if the card is expired and if the transaction amount is within limits.
### Server Module

Functions to receive transaction data, validate accounts, and check for sufficient funds.
## Testing
Each module includes comprehensive test functions to validate various scenarios, including happy paths and edge cases. Test results are printed to the console for verification.

## How to Use
Clone the repository.
Open the project in Microsoft Visual Studio.
Follow the folder structure specified in the project documentation.
Implement and test each module as per the provided specifications.
## Contributions
Feel free to contribute to this project by forking the repository, making changes, and submitting a pull request.

