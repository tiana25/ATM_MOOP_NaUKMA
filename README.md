# ATM_MOOP_NaUKMA
ATM application development on C++


## 1. Постановка задачі
### Мета: 
Розробка застосунку АТМ.

### Призначення: 
Базові функції АТМ: видача грошей, додавання грошей на рахунок, перекази між своїми та іншими картками, робота з банківськими даними.

## 2.	Характеристика об’єкта автоматизації
Створення АТМ-подібної системи, що дасть змогу користувачу банку контролювати свої рахунки, поповнювати рахунки, знімати кошти, створювати перекази між картками(своїми та іншими).

### 3. Вимоги до системи
* User-friendly інтерфейс
*	Можливість мати декілька рахунків, наявність таких видів рахунків:
  1. універсальний рахунок (можна робити переказати між своїми картками та на інші, знімати гроші, поповнювати рахунок,  перевіряти баланс на рахунку, змінювати та переглядати ліміт);
  2. депозитний рахунок (накопичувальний рахунок, на який можна просто класти гроші; після закінчення терміну депозиту гроші автоматично перейдуть на універсальний акаунт, знімати гроші до того моменту не можна);
  3. кредитний рахунок (рахунок, на якому лежать кредитні гроші, поповнення цього рахунку веде до зменшення кредитного боргу).
* Блокування картки при некоректному вводі паролю (3 рази)

## Можливості користувача:
* перегляд балансу всіх рахунків;
* зняття грошей з рахунків (універсальний та кредитний);
* переказ грошей на картки(свої та інші) ;
* перегляд історії транзакцій карти;
* зміна ліміту;
* перегляд ліміту;
* поповнення рахунків (у випадку кредитного акаунта – погашення боргу)

## Джерела розробки (використані технології)
C++, QT, SQLite

## ER-Model
![image](https://user-images.githubusercontent.com/60096558/137622885-87b36ed1-4c07-44e1-b67e-03090c1dc9b5.png)

## Як запустити
Якщо ви хочете протестувати проект - краще скористатися консольним варіантом, який відкривається в Visual Studio (перейдіть в папку StarBank).  
Для консольного варіанту:  
У main.cpp викликається метод test(), який тестує головні методи  
для роботи із ATM.  
Якщо Ви хочете протестувати систему власноруч,  
то далі буде atm.work(), який є закоментованим. Вам потрібно  
розкоментувати його та закоментувати метод  test().  

Якщо Ви потім захочете знову подивитися тести, то  
закоментуйте atm.work() та розкоментуйте test().  

Для варіанту з фронтом:  
Якщо хочете переглянути версію з фронтом, то проект треба запускати в програмі QT Creator.  
Qt Creator 4.12.4 (Community)  
Після встановлення Qt Creator на ваш комп'ютер, відкрийте папку з проектом (ATM_MOOP) та нажміть на ATM.pro.  
Проект відкриється в Qt Creator, де його можна запустити та протестувати.  

Щоб успішно працювала АТМ, перейдіть в DBPath.h у методі QString getPath()  
відкоментуйте рядок із абсолютним шляхом та пропишіть в ньому свій абсолютний шлях до файлу ATM.db  
та закоментуйте  return res+"ATM/ATM.db";  
Тобто вказати шлях до ATM.db на вашому локальному комп'ютері.  
![image](https://user-images.githubusercontent.com/60096558/137624484-959813bd-d592-4930-8860-2150ceeb710b.png)

Для запуску на  
!Деякі карти нижче можуть бути заблоковані (при необхідності їх можна розблокувати в ATM.db)  

Картки, які є в базі данних:  

Credit accounts:  
User 1) number: 7777, pin: 111  
User 2) number: 1234, pin: 123  
User 3) number: 4567, pin: 456  

Deposit accounts:  
User 1) number: 2355, pin: 111  
User 2) number: 8765, pin: 655  
User 3) number: 5667, pin: 677  

Universal accounts:  
User 1) number: 8886, pin: 234  
User 2) number: 4910, pin: 550  
User 3) number: 5656, pin: 565  

Зауважте, при
додаванні коштів на картку неможливо покласти, наприклад 700 грн за 1 раз,
необхідно, наприклад, покласти 200 грн, а потім 500.
Зауважте, що при будь-якому поповнені кредитного рахунку, сума на балансі не буде збільшуватися. Всі гроші йдуть на погашення кредитного боргу (якщо він є).


## Макети інтерфейсу (папка “Mockups”)
![image](https://user-images.githubusercontent.com/60096558/137623212-8a2232b1-9f11-4542-9500-aa68e9cb4d27.png)
![image](https://user-images.githubusercontent.com/60096558/137623213-3fe42df0-a6d9-4f79-a985-5a632c7ffbec.png)
![image](https://user-images.githubusercontent.com/60096558/137623214-a5ad32d3-76fd-49bf-9584-31209dc6c9b1.png)
![image](https://user-images.githubusercontent.com/60096558/137623217-1b69c04a-e95a-4592-84b4-dfd41a1a06e8.png)
![image](https://user-images.githubusercontent.com/60096558/137623220-274b7150-f906-496c-a218-1e28a09fd939.png)
![image](https://user-images.githubusercontent.com/60096558/137623221-1ea24d86-80c8-4995-b904-c658112a4a7d.png)
![image](https://user-images.githubusercontent.com/60096558/137623225-a2e244bf-9826-4488-b81d-ec1a4b6b3030.png)
![image](https://user-images.githubusercontent.com/60096558/137623228-08072909-6fac-4239-a71e-ee96a2e382b7.png)
![image](https://user-images.githubusercontent.com/60096558/137623230-59f215a2-780a-42e3-84f6-2e53ef8d34e5.png)
![image](https://user-images.githubusercontent.com/60096558/137623233-300554f0-dbe7-4ef4-a3ea-8e2990aa1a67.png)
