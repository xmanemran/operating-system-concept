#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

typedef struct {
  int day;
  int month;
  int year;
  struct list_head list;
} birth_day;

static void set_birthday(struct list_head *birthday_list, int day, int month, int year){
  birth_day *person_birthday = kmalloc(sizeof(*person_birthday), GFP_KERNEL);

  person_birthday->day = day;
  person_birthday->month = day;
  person_birthday->year = year;

  INIT_LIST_HEAD(&person_birthday->list);
  list_add_tail(&person_birthday->list, birthday_list);
}

static LIST_HEAD(birthday_list);

static int hello_init(void){
  printk(KERN_ALERT "Hello module\n");
  
  set_birthday(&birthday_list, 1, 8, 1983);
  set_birthday(&birthday_list, 3, 9, 1953);
  set_birthday(&birthday_list, 6, 2, 2000);
  set_birthday(&birthday_list, 3, 6, 2002);

  int i = 1;
  birth_day *person;

  list_for_each_entry(person, &birthday_list, list){
    printk(KERN_ALERT "Person %d birthday is: %d/%d/%d\n", i, person->day, person->month, person->year);
    i++;
  }

  return 0;
}

static void hello_exit(void){
  int i = 1;
  birth_day *person, *next;

  list_for_each_entry_safe(person, next, &birthday_list, list){
    printk(KERN_ALERT "Deleting person %d  is: %d/%d/%d\n", i, person->day, person->month, person->year);
    list_del(&person->list);
    kfree(person);
    i++;
  }
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
