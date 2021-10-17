# ATM_MOOP_NaUKMA
ATM application development on C++


## 1. Постановка задачі
### Мета: 
розробка застосунку АТМ.

### Призначення: 
базові функції АТМ: видача грошей, додавання грошей на рахунок, перекази між своїми та іншими картками, робота з банківськими даними.

## 2.	Характеристика об’єкта автоматизації

Створення АТМ-подібної системи, що дасть змогу користувачу банку контролювати свої рахунки, поповнювати рахунки, знімати кошти, створювати перекази між картками(своїми та іншими).

### 3. Вимоги до системи

•	User-friendly інтерфейс 
•	Можливість мати декілька рахунків, наявність таких видів рахунків:
- універсальний рахунок (можна робити переказати між своїми картками та на інші, знімати гроші, поповнювати рахунок,  перевіряти баланс на рахунку, змінювати та переглядати ліміт);
- депозитний рахунок (накопичувальний рахунок, на який можна просто класти гроші; після закінчення терміну депозиту гроші автоматично перейдуть на універсальний акаунт, знімати гроші до того моменту не можна);
-	кредитний рахунок (рахунок, на якому лежать кредитні гроші, поповнення цього рахунку веде до зменшення кредитного боргу).
•	Блокування картки при некоректному вводі паролю (3 рази)

## Можливості користувача:
•	перегляд балансу всіх рахунків;
• зняття грошей з рахунків (універсальний та кредитний);
• переказ грошей на картки(свої та інші) ;
• перегляд історії транзакцій карти;
• зміна ліміту;
• перегляд ліміту;
• поповнення рахунків (у випадку кредитного акаунта – погашення боргу) .

## Джерела розробки (використані технології)
C++, QT, SQLite

## ER-Model
![image](https://user-images.githubusercontent.com/60096558/137622885-87b36ed1-4c07-44e1-b67e-03090c1dc9b5.png)



