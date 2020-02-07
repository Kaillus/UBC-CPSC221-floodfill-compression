/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

/* No argument constructor */
template <class T>
Deque<T>::Deque():n1(/* your code here*/-1),n2(/* your code here*/-1){}
// n1 = min index - removal only 
// n2 = max index - removal and insertion 


/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    /**
     * @todo Your code here!
     */
     if (n1 == -1) {
         n1++; 
         n2++; 
     } else {
         n2++; 
     }
     data.push_back(newItem); 

}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    /**
     * @todo Your code here! 
     */

     T tempVal = data[n1];

     if (n1 == n2) {
         n1 = -1; 
         n2 = -1; // empty
         data.clear(); 
     } else {
         n1++; 
     }

     int num = (n2 - n1) + 1; //number ofs object in the Deque 

     if (n1 >= num) {
         vector<T> tempArray; 
         for (int i = n1; i <= n2; i++) {
             tempArray.push_back(data[i]);
             }
     
        data = tempArray; 
        n2 = n2 - n1;
        n1 = 0;
         
     }

     return tempVal; 
    
}


/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    /**
     * @todo Your code here! 
     */

     T tempVal = data[n2];
     data.pop_back(); 

     if (n1 == n2) {
         n1 = -1; 
         n2 = -1; 
         data.clear(); 
     } else {
         n2--;
     }
     
     int num = (n2 - n1) + 1; //number of objects in the Deque 

     if (n1 >= num) {
         vector<T> tempArray; 
         for (int i = n1; i <= n2; i++) {
             tempArray.push_back(data[i]);
             }
     
        data = tempArray; 
        n2 = n2 - n1;
        n1 = 0;
         
     }

     return tempVal; 


}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    /**
     * @todo Your code here! 
     */

     return data[n1];  
}



/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    /**
     * @todo Your code here! 
     */

     return data[n2];  
}



/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    /**
     * @todo Your code here! 
     */
     
     return (n2 == -1); 
}

