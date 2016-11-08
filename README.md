# CoreData_Study

- 在创建工程的时候，一定要选CoreData！一定要选CoreData！一定要选CoreData！

- 进行storyboard的页面设置，创建tableView控件，

- 将方法拖拽到ViewController中，进行实现，其中，引入了

  ```
  @property (strong, nonatomic) IBOutlet UITableView *tableView;

  - (IBAction)addModel:(id)sender{}
  ```

- 既然设置了tableView，就必须要导入 delegate 的方法，所以

  ```
  @interface ViewController ()<UITableViewDataSource, UITableViewDelegate, UIApplicationDelegate>
  ```

- 引入delegate协议之后，就必须实现 delegate 和 dataSource 的方法

  ```
  //返回分区中的行数
  - (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
      return self.dataSource.count;
  }

  //返回分区
  - (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
      return 1;
  }

  - (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
      
      UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell" forIndexPath:indexPath];
      
      Clothes *cloth = self.dataSource[indexPath.row];
      
      cell.textLabel.text = [NSString stringWithFormat:@"%@--%@",cloth.name,(int64_t)cloth.price];
      
      return cell;
  }
  ```

- 设置好必须实现的 delegate 和 dataSource 的方法之后，继续实现设置可以编辑表格，和点击每一cell的实现方法

  ```
  //允许编辑tableView
  - (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
      return YES;
  }

  - (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
      if (editingStyle == UITableViewCellEditingStyleDelete) {
          //删除数据源
          Clothes *cloth = self.dataSource[indexPath.row];
          
          [self.dataSource removeObject:cloth];
          
          //删除数据管理中的数据
          [self.myAppDelegate.persistentContainer.viewContext deleteObject:cloth];
          
          //将进行更改进行永久保存
          [self.myAppDelegate saveContext];
          
          //删除单元格
          [self.tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
      }
  }

  //点击cell修改数据
  - (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
      //1、找到模型对象
      Clothes *cloth = self.dataSource[indexPath.row];
      
      cloth.name = @"NIKE";
      
      //更改数据源,刷新单元行
      [self.tableView reloadRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationAutomatic];
      
      //更改之后进行永久保存
      [self.myAppDelegate saveContext];
      
  }
  ```

- 创建这些方法之后，设置xcdatamodel并导入，实现作用方法。

- 在每次添加数据之后，想数据存储，就先要使用`NSFetchRequest`查询数据，描述对象`NSSortDescriptor`

- 切记，更改数据之后，就应该调用`-(void)saveContext;`方法进行数据的永久保存

- 在需要删除数据的时候，首先要删除数据源`_dataSource`,再删除元祖`_tableView`的数据，最后实现`saveContext`永久保存

  ​
