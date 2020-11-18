# BookStore_2020
SJTU ACM 2020
Writen by PaperL

# Main.cpp
- 初始化`init()`
- 读入指令行`runCommand(string arg)`
# BookStore.h
- 全局变量
    - 当前状态	*(`Data_Basic.dat`用)*
        | 参数                                                         | 参数类型  | 长度(Byte) |
        | ------------------------------------------------------------ | --------- | ---------- |
        | 已登录账号及该账号已选中的图书（堆栈中每个元素为以下两个变量构成的`pair`） | 堆栈      |            |
        | 已登陆账号                                                   | userClass |            |
        | 选中图书在`Data_Book.dat`中的地址                            | 整型      | 4          |
        | 总支出                                                       | 浮点型    | 4          |
        | 总收入                                                       | 浮点型    | 4          |
        | 账号总数量                                                   | 整型      | 4          |
        | 图书总数量                                                   | 整型      | 4          |
    
- **init**() **初始化函数**
- **commandClass 指令类**
  
  - 指令参数	*(`Data_Basic.dat`用)*
    | 变量名              | 变量类型 | 长度(Byte) |
    | ------------------- | -------- | ---------- |
    | 指令类型            | 字符     | 1          |
    | 指令参数            | 字符串   | 250        |
    | 用户名              | 字符串   | 31         |
    | 执行情况(成功/失败) | 字符     | 1          |
    | 操作时间(time())    | 长长整型 | 8          |
  - runCommand(string arg)
  - recordCommand(commandClass t)
  - reportFinance()
  - reportEmployee()
  - log()
  - reportMyself()
  
- **userClass 账号类**
    - 账号参数	*(`Data_User.dat`用)*
        | 变量名 | 变量类型 | 长度(Byte) |
        | ---- | ---- | ---- |
        | userID | 字符串 | 30 |
        | name | 字符串 | 30 |
        | authority | 字符 | 1 |
        | password | 字符串 | 30 |
    - login(string userID, string password)
      
      - 重载函数 login(string userID)
    - logout()
    - userAdd(userClass t)
    - register(userClass t)
    - delete(int userID)
    - changePassword(int userID, string oldPass, string newPass)
      
      - 重载函数 changePassword(int userID, string newPass)
    
- **bookClass 图书类**
  
    - 图书参数	*(`Data_Book.dat`用)*
        | 变量名 | 变量类型 | 长度(Byte) |
        | ---- | ---- | ---- |
        | ISBN | 字符串 | 21 |
        | name | 字符串 | 61 |
	    | author | 字符串 | 61 |
	    | keyword | 字符串 | 61 |
	    | num | 整形 | 4 |
	- select(string ISBN)
	- modify(string arg)
	- import(int num, int price)
	- buy(string ISBN, int num)
	- show(string arg)
	- showFinance(int num)
	  
	  - 重载函数 showFinance()
	
- **unrolledLinkedListClass 块状链表类**

    - writeIndexData(string arg, int pointer, char type)
      - 重载函数 writeIndexData(string oldArg, string newArg, int pointer, char type)
    - readIndexData(string arg, char type)
    - deleteUserIndexData(string userID)
    - hash(string arg)	*(**private**)*
    
- **dataClass 其余数据类**
    - createUserData(userClass t)
    - changeUserData(string password, int pointer)
    - createBookData(string ISBN)
    - changeBookData(string arg, int pointer, char type)
      - 重载函数 changeBookData(int num, int pointer)
    - recordCommand(string name, string arg, char success)
# BasicFunc.cpp
**基础函数实现**
- **init**()
  功能：载入`Data_Basic.dat`中全局变量	*(如果第一次运行程序，建立空白文件，为全局变量赋初值)*
- **runCommand**(string arg)
  功能：读入并处理指令行；调用对应函数；返回一个`commandClass`类型变量
- **reportFinance**()
  功能：输出一张~~美观的~~财务报表
  所需权限：7
  指令：`report finance`
- **reportEmployee**()
  功能：输出一张~~美观的~~员工操作记录表
  所需权限：7
  指令：`report employee`
- **log**()
  功能：输出一张~~美观的~~日志包括所有操作和交易
  所需权限：7
  指令：`log`
- **reportMyself**()
  功能：输出一张~~美观的~~记录表包括自己的所有操作
  所需权限：3
  指令：`report myself`
# Command_User.cpp
**账户相关功能函数实现**

- **login**(string userID, string password)
  
  - 重载函数 login(string userID)	*高权限登录到低权限用户不需要填写密码*
  
  功能：验证`password`是否与`userID`匹配，若匹配则将该账户以`userClass`形式加入已登录账号堆栈
  所需权限：0
  指令：`su [user-id] [passwd]`
  
- **logout**()
  功能：弹出已登录账号堆栈中顶层`userClass`元素
  所需权限：1
  指令：`logout` 
- **userAdd**(userClass t)
  功能：新建一个权限级别小于自己的账户
  所需权限：3
  指令：`useradd [user-id] [passwd] [7/3/1] [name]` 
- **register**(userClass t)
  功能：新建一个权限1账户
  所需权限：0
  指令：`register [user-id] [passwd] [name]` 
- **delete**(int userID)
  功能：删除某账户
  所需权限：7
  指令：`delete [user-id]` 
- **changePassword**(int userID, string oldPass, string newPass)
  功能：验证`oldPass`是否与`userID`匹配，若匹配则将该账户密码改为`newPass`
  所需权限：1
  
  - 重载函数 changePassword(int userID, string newPass)	*(仅限权限7用户)*
    功能：修改`userID`账户密码为`newPass`

  指令：`passwd [user-id] [old-passwd] [new-passwd]`

# Command_Book.cpp
**图书相关功能函数实现**
- **select**(string ISBN)
  功能：选中一本书	*(若为空则创建该书)*
  所需权限：3
  指令：`select [ISBN]`
- **modify**(string arg)
  功能：修改选中书的参数
  所需权限：3
  指令：`modify -ISBN=[ISBN] -name=[name] -author=[author] -keyword=[keyword] -price=[price]`	*(参数数量、顺序不限)*
- **import**(int num, int price)
  功能：购进书
  所需权限：3
  指令：`import [quantity] [cost_price(in total)]`
- **buy**(string ISBN, int num)
  功能：购买书
  所需权限：1
  指令：`buy [ISBN] [quantity]`
- **show**(string arg)
  功能：输出符合条件的书
  所需权限：1
  指令：`show -ISBN=[ISBN] -name=[name] -author=[author] -keyword=[keyword]` *(参数至多一项)*
- **showFinance**(int num)
  功能：输出近`num`次进出货操作的收入支出
  
  - 重载函数 showFinance()
    功能：输出总收入与支出
  
  所需权限：7
  指令：`show finance [time]`
# IO_UnrolledLinkedList.cpp
**块状链表读写相关函数实现**

- **writeIndexData**(string arg, int pointer, char type)
  功能：根据`arg`的哈希值，将`pointer`存入相应文件	*(新增数据)*

  - 重载函数 writeIndexData(string oldArg, string newArg, int pointer, char type)	*(覆盖写入图书数据)*
    功能：在相应文件内，先根据`oldArg`的哈希值删除旧数据，再根据`newArg`的哈希值，存入新数据
  
  *(不同 `type` 参数对应 `Index_Userid.dat` / `Index_ISBN.dat` / `Index_Author.dat` / `Index_Name.dat` / `Index_Keyword.dat`，其中同一本图书在`Index_Keyword.dat`中可有多个数据)*
  
- **readIndexData**(string arg, char type)
  功能：返回输入数据在相应文件内的地址	*(`type`参数同上)*

- **deleteUserIndexData**(string userID)	*(删除账号数据)*
  功能：根据`userID`的哈希值，删除`Index_Userid.dat`内对应数据

- **hash**(string arg)	*(**private**)*
  功能：返回该字符串的哈希值	*(二次哈希)*

# IO_Data.cpp
**其余数据文件读写函数实现**

- **createUserData**(userClass t)
  功能：在`Data_User.dat`内创建账户`t`，并返回该账户于`Data_User.dat`内地址

- **changeUserData**(string password, int pointer)
  功能：更新`Data_User.dat`内`pointer`处账户的密码
  
- **createBookData**(string ISBN)
  功能：在`Data_Book.dat`内创建该图书，并返回该图书于`Data_User.dat`内地址

- **changeBookData**(string arg, int pointer, char type)
  功能：更新`Data_Book.dat`内`pointer`处数据
  *(不同`type`参数对应修改项为`ISBN` / `name` / `author` / `keyword` / `price`)*
  - 重载函数 changeBookData(int num, int pointer)
    功能：使`Data_Book.dat`内`pointer`处图书的数量增加`num`
  
- **recordCommand**(commandClass t)
  功能：储存操作至`Data_Basic.dat`文件末

# 文件存储
**软件运行所需文件及其功能**

- **Data_Basic**.dat
  - 账号总数量
  - 图书总数量
  - 总支出
  - 总收入
  - 操作日志
- **Data_User**.dat
  - 按创建顺序存储userClass元素
- **Data_Book**.dat
  - 按创建顺序存储bookClass元素
- **Index_Userid**.dat
  - 以**块状链表**升序存储`userID`的**哈希值**及该账号于`Data_User.dat`中的位置
- **Index_ISBN**.dat
  - 以块状链表升序存储`ISBN`的哈希值及该图书数据于`Data_Book.dat`中的位置
- **Index_Author**.dat
  - 以块状链表升序存储`author`的哈希值及该图书数据于`Data_Book.dat`中的位置
- **Index_Name**.dat
  - 以块状链表升序存储`name`的哈希值及该图书数据于`Data_Book.dat`中的位置
- **Index_Keyword**.dat
  - 以块状链表升序存储`keyword`的哈希值及该图书数据于`Data_Book.dat`中的位置

