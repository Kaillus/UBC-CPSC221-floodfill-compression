/**
 * @file vor.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
//included within  "vor.h" for template instantiation



/* vorDotDFS given as an example for PA2 */
animation filler::vorDotDFS(PNG& img, double density,
                                int dotGrid,int dotSize, int frameFreq)
{
    dotColorPicker a(dotGrid,dotSize);
    return vor<Stack>(img, density, a, frameFreq);
}

animation filler::vorSolidDFS(PNG& img, double density, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    solidColorPicker a;
    return vor<Stack>(img, density, a, frameFreq);
}

animation filler::vorFadeDFS(PNG& img, double density, double fadeFactor, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    fadeColorPicker a(fadeFactor);
    return vor<Stack>(img, density, a, frameFreq);
}


/* vorDotBFS given as an example for PA2 */
animation filler::vorDotBFS(PNG& img, double density,
                                int dotGrid,int dotSize, int frameFreq)
{
    dotColorPicker a(dotGrid, dotSize);
    return vor<Queue>(img, density, a, frameFreq);
}

animation filler::vorSolidBFS(PNG& img, double density, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    solidColorPicker a;
    return vor<Queue>(img, density, a, frameFreq);
}

animation filler::vorFadeBFS(PNG& img, double density, double fadeFactor, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    fadeColorPicker a(fadeFactor);
    return vor<Queue>(img, density, a, frameFreq);
}


bool withinEuclideanVOR(point p) {
    int x = p.x; 
    int y = p.y; 
    int level = p.level; 
    center c = p.c; 


    //int distance = (sqrt( pow(x - c.x, 2) + pow(y - c.y, 2) ));
    //int eucdistance = level + 1; 
    int distance = ((x - c.x) * (x - c.x) + (y - c.y) * (y - c.y));
    int eucdistance = (level + 1) * (level + 1); 
    return (distance <= eucdistance); 
    //return ((level <= distance) && (distance <= level + 1) );

    //return ((x - c.x) * (x - c.x) + (y - c.y) * (y - c.y)) <= (p.level + 1) * (p.level +1); 

    //((p.x - p.c.x) * (p.x - p.c.x) + (p.y - p.c.y ) * (p.y - p.c.y)) <= ((p.level + 1) * (p.l + 1)
}


template <typename TwoD>
void filler:: addPoint(PNG& img, point& p, colorPicker& fillColor, OrderingStructure<point>& centerOS, 
    TwoD & processed, int& framesSoFar, int frameFreq, animation& output) {


    if (p.x >= 0 && p.x < (int) img.width() && p.y >=0 && p.y  < (int) img.height()) { // check if is in the img 
        if (processed[p.y][p.x]==0) { // check if its processed 
            HSLAPixel * c = img.getPixel(p.x,p.y); 
            * c = fillColor(p); 
            p.level++;  
            processed[p.y][p.x] = 1;
            centerOS.add(p); 
            framesSoFar++; 
            if (framesSoFar % frameFreq == 0) {
                output.addFrame(img);
                //cout<< "here!!" << endl; 

            }
        }

    }
}


template <template <class T> class OrderingStructure>
animation filler::vor(PNG& img, double density, colorPicker& fillColor,
                       int frameFreq)
{

    /**
     * @todo You need to implement this function!
     *
     * This is a general description of a space filling algorithm, where 
     * the space is partitioned into a set of regions each color of which
     * is determined by the color of a point 
     * chosen from an original image. We call those original points
     * "centers." (See pictures in the specification.)
     *
     * The algorithm requires ordering structures used to orchestrate
     * the sequence of points filled. This structure type info is passed to the 
     * fill algorithm via its template parameter. For a breadth-first fill,
     * we use Queues, and for a depth-first fill, we use Stacks. Function
     * vorDotDFS provides an example call to function vor.
     * 
     * The algorithm includes the following steps:
     * 1) you will first select a random set
     * of coordinates (and their colors) to use as centers from which to
     * begin the fill. (this function is in file vor_given.cpp -- for 
     * testing purposes, you'll use regularly spaced points, rather than 
     * random.)
     * 2) Initialize a structure to use to maintain a collection of 
     * ordering structures
     *
     * 3) Initialize the fill: For each center c, in round-robin order, 
     *     do the following:
     *     a)  add the center to the its ordering structure. (every center 
     *         its own!
     *     b)  mark the location of that center as processed (the way you 
     *         do this is up to you!)
     *     c)  we have a choice to actually set the color of the pixel in 
     *         the fill when we add or when we remove. In our test cases, 
     *         we assume that you will change a color when a point is 
     *         added to a structure. (this is mostly relevant for checking 
     *         the animations.)
     *
     * 5) Complete the fill: Until all ordering structures (OS) are empty, 
     *    do the following for each OS, in a round robin order, indexing
     *    the iterations by k (an integer distance from the center):
     *    
     *      For each point less than or equal to distance k from its center:
     *      a)Remove the  point p from the ordering structure, and then...
     *
     *        i.    add p's unprocessed neighbors to the ordering structure if 
     *              they are within the appropriate distance from the center. We 
     *              describe this more carefully below. We call these the "valid"
     *              neighbors.
     *        ii.    use the colorPicker to set the new color of the valid neighbors.
     *        iii.    mark the valid neighbors as processed.
     *        iv.    as each neighbor is processed, if it is an appropriate 
     *              frame, send the current PNG to the
     *              animation (as described below).
    *
     *      b) When implementing your breadth-first and depth-first fills, 
     *            you will need to explore neighboring pixels in some order.
     *
     *        For this assignment, each pixel p has *up to* 8 neighbors, consisting of 
     *        the 8 pixels who share an edge with p. (We leave it to
     *        you to describe those 8 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! 
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        ** UP(-y), UPLEFT(-x,-y), LEFT(-x), LEFTDOWN(-x,+y), DOWN(+y), 
     *        DOWNRIGHT(+x,+y), RIGHT(+x), RIGHTUP(+x,-y)**
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        TWO IMPORTANT NOTES: 
     *        1) *UP* here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction. 
     *        2) not all of the 8 neighbors will be processed at every iteration of the
     *        while loop. You must assure that all vertices distance k or less
     *        from the center are processed (colored and put on the queue) before
     *        ANY whose distance is *greater than* k. k is a non-negative integer. 
     *        Finally, distance is the standard Euclidean distance  (computed 
     *        using the Pythagorean theorem). It is this requirement that assures
     *        that the fill grows outward from the center in the shape of a circle,
     *        rather than a diamond or a square. 
     *
     *      c) For every g pixels filled, **starting at the gth pixel**, you
     *        must add a frame to the animation, where g = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     *      d) Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */



     /* Your code here. As a point of reference, we used three different helper
      * functions to complete this code. You may add as many as you wish, since
      * we will be grading vor.h. File "vor_given.cpp also includes the function
      * used to generate the original set of centers. 
      */
    vector<center> centers = randSample(img, density); //1)
 	Queue<OrderingStructure<point> > collection; // Initialize a structure - collection of centerOS
    //collection.reserve(centers.size()); // don't need it bc collection is Queue

    PNG newImg(img.width(), img.height()); 

    animation output;
    int framesSoFar = 0;


// processecd marker 
    vector<vector<int>> processed;

    for (int l = 0; l < (int) img.height(); l++) { //lines

        std::vector<int> sec;
        for (int k = 0; k < (int) img.width(); k++) { //columns
            int p = 0; // all not processed 
            sec.push_back(p);
        }
        
        processed.push_back(sec);
    }

    // for (int i = 0; i < (int) img.height(); i++) {
    //     for (int j = 0; j < (int) img.width(); i++) {
    //         processed[i][j] = 0;
    //     }
    // }

    for (int i = 0; i < (int) centers.size(); i++) { //3a ??
        point pt(centers[i]);

        if (pt.x >= 0 && pt.x < (int) img.width() && pt.y >=0 && pt.y < (int) img.height()) {
            if (processed[pt.y][pt.x] == 0) {
                OrderingStructure<point> centerOS;
                centerOS.add(pt); /////////////////////////////// need to make conditions before adding the point to the centerOS 
                //collection.push_back(centerOS);
                collection.enqueue(centerOS); 
                HSLAPixel * pixel = newImg.getPixel(pt.x, pt.y);
                *(pixel) = fillColor(pt);
                processed[pt.y][pt.x] = 1;
                framesSoFar++; 
                if (framesSoFar % frameFreq == 0) {
                    output.addFrame(img);
                    //cout<< "here!!" << endl; 

                }
            }
        }
    }
    //output.addFrame(newImg); 


   
/*
    vector<vector<bool>> processed; //prep for 3b)

    for (int l = 0; l < (int) img.height(); l++) { //lines

        std::vector<bool> sec;
        for (int k = 0; k < (int) img.width(); k++) { //columns
            bool p = false;
            sec.push_back(p);
        }
        
        processed.push_back(sec);
    }


    for (int i = 0; i < (int) centers.size(); i++) { //3b)
        processed[centers[i].y][centers[i].x] = true;
    } // centers are processed 

 */

/*
    bool * processed = new bool[img.width() * img.height()];
    for (int i = 0; i < img.width() * img.height(); i++)
        processed[i] = 0;

    for (int i = 0; i < (int) centers.size(); i++) { //3b)
        processed[img.width() * centers[i].y + centers[i].x] = 1;
    } // centers are processed 
*/


    while (!collection.isEmpty()) {
        OrderingStructure<point> currOS = collection.dequeue();

        //if (currOS.peek().level != currentLevel) currentLevel++; 
        //bool firstElementFetched = false;
        int currentLevel = -1; 

        while (!currOS.isEmpty()) {
            if (currentLevel == -1) {
                currentLevel = currOS.peek().level;
            }

            if (currentLevel == currOS.peek().level) {
                point curr = currOS.remove(); 
                
                    point up(curr); 
                    up.y--; 
                    if (withinEuclideanVOR(up)) {
                        addPoint(newImg, up, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    point upleft(curr);
                    
                    //upleft.y--; // THIS SHOULD NOT BE HERE!!!!! 

                    upleft.y--; 
                    upleft.x--; 
                    if (withinEuclideanVOR(upleft)) {
                    //cout << "what" << endl; 
                        addPoint(newImg, upleft, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }


                    point left(curr); 
                    left.x--;
                    if (withinEuclideanVOR(left)) {
                        addPoint(newImg, left, fillColor, currOS, processed, framesSoFar, frameFreq, output); 
                    }

                    point leftdown(curr);
                    leftdown.x--; 
                    leftdown.y++; 
                    if (withinEuclideanVOR(leftdown)) {
                        addPoint(newImg, leftdown, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    point down(curr); 
                    down.y++;
                    if (withinEuclideanVOR(down)) {
                        addPoint(newImg, down, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    point downright(curr);
                    downright.y++; 
                    downright.x++; 
                    if (withinEuclideanVOR(downright)) {
                        addPoint(newImg, downright, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    point right(curr); 
                    right.x++;
                    if (withinEuclideanVOR(right)) {
                        addPoint(newImg, right, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    point rightup(curr); 
                    rightup.x++; 
                    rightup.y--; 
                    if (withinEuclideanVOR(rightup)) {
                        addPoint(newImg, rightup, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    //currOS.remove(); 

            } else {

                if (!currOS.isEmpty()) {
                    collection.enqueue(currOS); 
                    break;
                } else {
                    collection.remove(); 
                }
            }

        }
    }

    output.addFrame(newImg); 
    return output; 





/*

    int totalPoints = (img.height() * img.width()) - centers.size(); 
    int currentLevel = 0; 

    while (totalPoints != 0) {
    	
        OrderingStructure<point> currOS = collection.dequeue();

    	if (currOS.peek().level != currentLevel) currentLevel++; 
        //cout << "level" << currentLevel << endl; 

    	while (!currOS.isEmpty()) { // looping inside of currOS 
    		point curr = currOS.peek(); 

    		if (curr.level == currentLevel) {


                    point up(curr); 
                    up.y--; 
                    if (withinEuclideanVOR(up)) {

                        cout << "up" << endl;
                        addPoint(newImg, up, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    point upleft(curr);
                    
                    //upleft.y--; // THIS SHOULD NOT BE HERE!!!!! 
                    upleft.y--; 
                    upleft.x--; 
                    if (withinEuclideanVOR(upleft)) {

                        cout << "upleft" << endl;
                        addPoint(newImg, upleft, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                        totalPoints--; 
                    }


                    point left(curr); 
                    left.x--;
                    if (withinEuclideanVOR(left)) {
                        cout << "left" << endl;
                        addPoint(newImg, left, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                        totalPoints--; 
                    }

                    point leftdown(curr);
                    leftdown.x--; 
                    leftdown.y++; 
                    if (withinEuclideanVOR(leftdown)) {

                        cout << "leftdown" << endl;
                        addPoint(newImg, leftdown, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                        totalPoints--; 
                    }

                    point down(curr); 
                    down.y++;
                    if (withinEuclideanVOR(down)) {
                        cout << "down" << endl;
                        addPoint(newImg, down, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                        totalPoints--; 
                    }

                    point downright(curr);
                    downright.y++; 
                    downright.x++; 
                    if (withinEuclideanVOR(downright)) {
                        cout << "downright" << endl;
                        addPoint(newImg, downright, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                        totalPoints--; 
                    }

                    point right(curr); 
                    right.x++;
                    if (withinEuclideanVOR(right)) {
                        addPoint(newImg, right, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                        totalPoints--; 
                    }

                    point rightup(curr); 
                    rightup.x++; 
                    rightup.y--; 
                    if (withinEuclideanVOR(rightup)) {

                        cout << "rightup" << endl; 
                        addPoint(newImg, rightup, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                        totalPoints--; 
                    } 


                    currOS.remove(); 
                    cout << "weee" << endl; 

                    if (currOS.isEmpty()) {
                        collection.remove(); 
                        cout << "remove it when empty" << endl; 
                    }


    		} else {
                cout << "ELLLLLLLLLLLSE" << endl; 

    			if (!currOS.isEmpty()) {
    				collection.enqueue(currOS); 
    				break;
    			} else {
    				collection.remove(); 
    			}
    		}

    	}
    }
    cout << "last" << endl; 

    output.addFrame(newImg); 
    return output; 
*/
    /*
    //int levelTracker = 0; 
    int collecIndex = -1;
    int currentLevel = 0;
    int temp = 0; 


    while(!collection.empty()){
        collecIndex++; 
        int collecIndexMod = collecIndex % centers.size();

        OrderingStructure<point> currOS = collection[collecIndexMod];

        if(currentLevel != currOS.peek().level) {
            currentLevel++; 
        }

        if (currOS.isEmpty()) {
            collection.erase(collection.begin() + collecIndexMod);
        }

        while(!currOS.isEmpty()){
            if (currentLevel != currOS.peek().level) {
            //cout << "break?" << endl; 
                break; 

            } else {
                point curr = currOS.peek();

                    point up(curr); 
                    up.y--;
                    if (withinEuclideanVOR(up)) {
                        addPoint(newImg, up, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    point upleft(curr);
                    upleft.y--; 
                    upleft.x--; 
                    if (withinEuclideanVOR(upleft)) {
                        addPoint(newImg, upleft, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    //cout << "what" << endl; 

                    point left(curr); 
                    left.x--;
                    if (withinEuclideanVOR(left)) {
                        addPoint(newImg, left, fillColor, currOS, processed, framesSoFar, frameFreq, output); 
                    }

                    point leftdown(curr);
                    leftdown.x--; 
                    leftdown.y++; 
                    if (withinEuclideanVOR(leftdown)) {
                        addPoint(newImg, leftdown, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    point down(curr); 
                    down.y++;
                    if (withinEuclideanVOR(down)) {
                        addPoint(newImg, down, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    point downright(curr);
                    downright.y++; 
                    downright.x++; 
                    if (withinEuclideanVOR(downright)) {
                        addPoint(newImg, downright, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    point right(curr); 
                    right.x++;
                    if (withinEuclideanVOR(right)) {
                        addPoint(newImg, right, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                    point rightup(curr); 
                    rightup.x++; 
                    rightup.y--; 
                    if (withinEuclideanVOR(rightup)) {
                        addPoint(newImg, rightup, fillColor, currOS, processed, framesSoFar, frameFreq, output);
                    }

                currOS.remove(); 
                temp++; 

            } 
        } 

    }

    

    output.addFrame(newImg);
    return output; 

    */


}

// template <template <class T> class OrderingStructure>
// bool allEmpty(vector<OrderingStructure<point>> vector) {
//     for (int i = 0; i < (int) vector.size(); i++) {
//         if (!vector[i].isEmpty()) {
//             return false;
//         }
//     }
//     return true;
// }