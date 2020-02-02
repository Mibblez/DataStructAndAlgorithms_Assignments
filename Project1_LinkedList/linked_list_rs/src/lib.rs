pub mod linked_list;

#[cfg(test)]
mod tests {
    use crate::linked_list::LinkedList;

    #[test]
    fn check_empty() {
        let ll = LinkedList::new();
        assert_eq!(ll.is_empty(), true);
    }

    #[test]
    fn check_insert(){
        let mut ll = LinkedList::new();

        assert_eq!(ll.insert(1,1.1).is_ok(), true);
        assert_eq!(ll.insert(2,2.2).is_ok(), true);
        assert_eq!(ll.insert(3,3.3).is_ok(), true);
        assert_eq!(ll.insert(4,4.4).is_ok(), true);

        assert_eq!(ll.insert(4, 5.5).is_err(), true);
    }

    #[test]
    fn check_print(){
        println!();
        println!("Testing print...");
        let mut ll = LinkedList::new();

        print!("Empty list: ");
        ll.print();

        ll.insert(1, 1.1);
        ll.insert(2, 2.2);
        ll.insert(3, 3.3);
        ll.insert(4, 4.4);

        print!("List with four elements: ");
        ll.print();

        println!();
    }

    #[test]
    fn check_length(){
         let mut ll = LinkedList::new();

         assert_eq!(ll.list_length(), 0);

         ll.insert(1, 1.1);
         ll.insert(2, 2.2);
         ll.insert(3, 3.3);
         ll.insert(4, 4.4);
         ll.insert(5, 5.5);
         ll.insert(6, 6.6);

         assert_eq!(ll.list_length(), 6);
     }

    #[test]
    fn check_search(){
        let mut ll = LinkedList::new();

        ll.insert(1, 1.1);
        ll.insert(2, 2.2);
        ll.insert(3, 3.3);
        ll.insert(4, 4.4);
        ll.insert(5, 5.5);
        ll.insert(6, 6.6);

        assert_eq!(ll.search(5), Some(5.5));
        assert_eq!(ll.search(10), None);

    }

    #[test]
    fn check_clear(){
        let mut ll = LinkedList::new();

        ll.insert(1, 1.1);
        ll.insert(2, 2.2);
        ll.insert(3, 3.3);
        ll.insert(4, 4.4);
        ll.insert(5, 5.5);
        ll.insert(6, 6.6);

        assert_eq!(ll.list_length(), 6);

        ll.clear_list();

        assert_eq!(ll.list_length(), 0);

        ll.insert(1, 1.1);
        ll.insert(2, 2.2);
        ll.insert(3, 3.3);
        ll.insert(4, 4.4);

        assert_eq!(ll.list_length(), 4);
    }

    #[test]
    fn check_delete() {
        let mut ll = LinkedList::new();

        assert_eq!(ll.delete(99).is_err(), true);

        ll.insert(1, 1.1);
        ll.insert(2, 2.2);

        assert_eq!(ll.delete(2).is_ok(), true);

        assert_eq!(ll.search(1), Some(1.1));
        assert_eq!(ll.search(2), None);

        ll.insert(2, 2.2);
        ll.insert(3, 3.3);
        ll.insert(4, 4.4);

        assert_eq!(ll.search(1), Some(1.1));
        assert_eq!(ll.search(2), Some(2.2));
        assert_eq!(ll.search(3), Some(3.3));
        assert_eq!(ll.search(4), Some(4.4));

        assert_eq!(ll.delete(3).is_ok(), true);

        assert_eq!(ll.search(1), Some(1.1));
        assert_eq!(ll.search(2), Some(2.2));
        assert_eq!(ll.search(3), None);
        assert_eq!(ll.search(4), Some(4.4));

        assert_eq!(ll.delete(1).is_ok(), true);

        assert_eq!(ll.search(1), None);
        assert_eq!(ll.search(2), Some(2.2));
        assert_eq!(ll.search(3), None);
        assert_eq!(ll.search(4), Some(4.4));

        assert_eq!(ll.delete(10).is_err(), true);
    }
}
