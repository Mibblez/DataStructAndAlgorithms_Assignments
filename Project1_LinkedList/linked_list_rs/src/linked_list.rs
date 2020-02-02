use std::mem;
use std::io::ErrorKind;

enum Link {
    Empty,
    More(Box<ListElement>),
}

impl PartialEq for Link {
    fn eq(&self, other: &Self) -> bool {
        mem::discriminant(self) == mem::discriminant(other)
    }

    fn ne(&self, other: &Self) -> bool {
        mem::discriminant(self) != mem::discriminant(other)
    }
}

struct ListElement {
    key: i32,
    data: f64,
    next: Link,
}

pub struct LinkedList {
    head: Link,
}

impl LinkedList {
    pub fn new() -> Self{
        LinkedList{head: Link::Empty}
    }

    pub fn list_length(&self) -> i32 {
        fn length_recursion(link: &Link) -> i32 {
            return match link {
                Link::Empty => {
                    0
                }
                Link::More(ref element) => {
                    let next_element = &element.next;
                    1 + length_recursion(&next_element)
                }
            };
        }

        return length_recursion(&self.head);
    }

    /// Inserts a ListElement to the end of the list with the provided key and float value.
    /// Returns an error if the key already exists in the list.
    pub fn insert(&mut self, k: i32, f: f64) -> std::io::Result<()> {
        fn insert_recursion(link: &mut Link, k:i32, f:f64) -> std::io::Result<()> {
            return match link {
                Link::Empty => {
                    let new_element = Box::new(ListElement {
                        key: k,
                        data: f,
                        next: Link::Empty,
                    });

                    *link = Link::More(new_element);
                    Ok(())
                }
                Link::More(ref mut element) => {
                    if element.key == k {
                        return Err(std::io::Error::new(
                            ErrorKind::AlreadyExists, format!("Key {} already exists", k)));
                    }

                    let next_element = &mut element.next;
                    insert_recursion(next_element, k, f)
                }
            };
        }

        insert_recursion(&mut self.head, k, f)
    }

    /// Removes a ListElement from the list according to the key provided. List order is preserved.
    /// Returns an error if the key does not exist in the list.
    pub fn delete(&mut self, k:i32) -> std::io::Result<()> {
        if self.is_empty() {
            return Err(std::io::Error::new(
                ErrorKind::NotFound, format!("Key {} does not exist", k)));
        }

        fn delete_recursion(link: &mut Link, k:i32) -> std::io::Result<()> {
            return match link {
                Link::More(ref mut element) => {
                    let next_link = &mut element.next;

                    if element.key == k {
                        // Found the key we want to delete
                        return if element.next == Link::Empty {
                            *link = Link::Empty;
                            Ok(())
                        } else {
                            // Change link to the next link by stealing a value out of a borrow by replacing it with another value
                            *link = mem::replace(&mut element.next, Link::Empty);
                            Ok(())
                        }

                    }
                    delete_recursion(next_link, k)
                }
                Link::Empty => {
                    Err(std::io::Error::new(
                        ErrorKind::NotFound, format!("Key {} does not exist", k)))
                }
            };
        }

        return delete_recursion(&mut self.head, k);
    }

    /// Returns an Option containing the float value associated with the provided key.
    /// Returns None if the key does not exist in the list.
    pub fn search(&self, k: i32) -> Option<f64>{
        fn search_recursion(link: &Link, k: i32) -> Option<f64> {
            return match link {
                Link::Empty => {
                    None
                }
                Link::More(ref element) => {
                    if element.key == k {
                        return Some(element.data);
                    }
                    search_recursion(&element.next, k)
                }
            };
        }

        return search_recursion(&self.head, k);
    }

    pub fn is_empty(&self) -> bool{
        if self.head == Link::Empty { true }
        else { false }
    }

    /// Removes all ListElements from the list.
    pub fn clear_list(&mut self) {
        self.head = Link::Empty;
    }

    pub fn print(&self) {
        print!("{{");
        fn print_recursion(link: &Link){
            match link {
                Link::Empty => {
                    println!("}}");
                }
                Link::More(ref element)=> {
                    print!("[{}:{}]", element.key, element.data);
                    let next_element = &element.next;
                    print_recursion(next_element);
                }
            };

        }
        print_recursion(&self.head);
    }
}

