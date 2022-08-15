/* Your code here! */
#include "maze.h"
#include <iostream>

using namespace std;



/**No-parameter constructor.
   Creates an empty maze.**/
SquareMaze::SquareMaze(){
    // m_width = 0;
    // m_height = 0;
    // dest = 0;
}


/**Makes a new SquareMaze of the given height and width.
   If this object already represents a maze it will clear all the existing data before doing so. 
   You will start with a square grid (like graph paper) with the specified height and width. 
   You will select random walls to delete without creating a cycle, until there are no more walls 
   that could be deleted without creating a cycle. Do not delete walls on the perimeter of the grid.**/
void SquareMaze::makeMaze(int width, int height){
    int rand_width = 0;
    int rand_height = 0;
    int select = 0;
    bool condition = true;
    m_width = width;
    m_height = height;
    int m_size = width * height;
    d_maze.addelements(m_size);
    for(int i = 0; i < m_size; i++){
        rht.push_back(1);
        dwn.push_back(1);
    } 
    while(d_maze.size(0) < m_size){  
        rand_width = rand() % m_width;
        rand_height = rand() % m_height;
        select = rand() % 2;
        if (select == 1 && rand_width < m_width - 1 && (d_maze.find(rand_height * m_width + rand_width) != d_maze.find(rand_height * m_width + rand_width + 1))){
                condition = false;
                setWall(rand_width, rand_height, 0, condition);
                d_maze.setunion(rand_height * m_width + rand_width, rand_height * m_width + rand_width + 1);
        }
        else if (select == 0 && rand_height < m_height - 1 && (d_maze.find(rand_height * m_width + rand_width) != d_maze.find(rand_height * m_width + rand_width + m_width))){
                condition = false;
                setWall(rand_width, rand_height, 1, condition);
                d_maze.setunion(rand_height * m_width + rand_width, rand_height * m_width + rand_width + m_width);
        }
        else{
        //do nothing
        }
    }

}





/**This uses your representation of the maze to determine whether it is possible to travel 
   in the given direction from the square at coordinates (x,y).
   For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).
   dir = 0 represents a rightward step (+1 to the x coordinate)
   dir = 1 represents a downward step (+1 to the y coordinate)
   dir = 2 represents a leftward step (-1 to the x coordinate)
   dir = 3 represents an upward step (-1 to the y coordinate)**/
bool SquareMaze::canTravel(int x, int y, int dir)const{
    bool result = true;
    if (dir == 0){
        if (rht[y * m_width + x] == 0){
            result = true;
        }
        else{
            result = false;
        }
    }
    else if (dir == 1){
        if (dwn[y * m_width + x] == 0){
            result = true;
        }
        else{
            result = false;
        }
    }
    else if (dir == 2){
        if ((x != 0) && (rht[y * m_width + x - 1] == 0)){
            result = true;
        }
        else{
            result = false;
        }
    }
    else{          //dir == 3
        if ((y != 0) && (dwn[y * m_width + x - m_width] == 0)){
            result = true;
        }
        else{
            result = false;
        }
    }
    return result;
}



/**Sets whether or not the specified wall exists**/
void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if (dir == 0){
        if (exists == true){
            rht[y * m_width + x] = 1;
        }
        else{
            rht[y * m_width + x] = 0;
        }
    }
    else if (dir == 1){
        if (exists == true){
            dwn[y * m_width + x] = 1;
        }
        else{
            dwn[y * m_width + x] = 0;
        }
    }
    else{
        //do nothing
    }
}





/**Solves this SquareMaze
   For each square on the bottom row (maximum y coordinate), 
   there is a distance from the origin (i.e. the top-left cell), 
   which is defined as the length (measured as a number of steps) of the only path 
   through the maze from the origin to that square
   Select the square in the bottom row with the largest distance from the origin as the destination of the maze. 
   solveMaze() returns the winning path from the origin to the destination as a vector of integers, 
   where each integer represents the direction of a step, using the same encoding as in canTravel().
   If multiple paths of maximum length exist, use the one with the destination cell that has the smallest x value.**/
vector<int> SquareMaze::solveMaze(){
    int x = 0;
    int y = 0;
    int curr = 0;
    int m_size = m_width * m_height;
    vector<int> prev;  
    vector<int> distance; 
    vector<int> solution;
    queue<int> bfs;


    prev.push_back(0); 
    distance.push_back(0);
    for(int i = 1; i < m_size; i++){
      prev.push_back(-1); 
      distance.push_back(0);
    }
    bfs.push(0);
    while(!bfs.empty()){
      curr = bfs.front();
      x = curr % m_width;
      y = curr / m_width;
      bfs.pop();

      if(canTravel(x, y, 0) && prev[curr + 1] == -1){
          bfs.push(curr + 1);
          prev[curr + 1] = curr;
          distance[curr + 1] = distance[curr] + 1;
      }
      if(canTravel(x, y, 1) && prev[curr + m_width] == -1){
          bfs.push(curr + m_width);
          prev[curr + m_width] = curr;
          distance[curr + m_width] = distance[curr] + 1;
      }
      if(canTravel(x, y, 2) && prev[curr - 1] == -1){
          bfs.push(curr - 1);
          prev[curr - 1] = curr;
          distance[curr - 1] = distance[curr] + 1;
      }
      if(canTravel(x, y, 3) && prev[curr - m_width] == -1){
          bfs.push(curr - m_width);
          prev[curr - m_width] = curr;
          distance[curr - m_width] = distance[curr] + 1;
      }
    }

    int tmp = m_width * (m_height - 1);
    for(int k = 0; k < m_width; k++){
        if(distance[m_width * (m_height - 1) + k] > distance[tmp]){
            tmp = m_width * (m_height - 1) + k;
        }
    }
    dest = tmp;
    curr = dest; 
    while(curr != 0){
      if(prev[curr] == curr - 1){
        solution.push_back(0);
      }
      if(prev[curr] == curr - m_width){
        solution.push_back(1);
      }
      if(prev[curr] == curr + 1){
        solution.push_back(2);
      }
      if(prev[curr] == curr + m_width){
        solution.push_back(3);
      }
      curr = prev[curr];
    }
    reverse(solution.begin(), solution.end());

  return solution;

}





/**Draws the maze without the solution
   First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1). 
   where height and width were the arguments to makeMaze. Blacken the entire topmost row and 
   leftmost column of pixels, except the entrance (1,0) through (9,0). For each square in the maze, 
   call its maze coordinates (x,y). If the right wall exists, then blacken the pixels 
   with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. If the bottom wall exists, 
   then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
   The resulting PNG will look like the sample image, except there will be no exit from the maze 
   and the red line will be missing
**/
PNG * SquareMaze::drawMaze()const{
    PNG* png_new = new PNG(m_width * 10 + 1, m_height * 10 + 1);
    int maze_w = m_width * 10 + 1;
    int maze_h = m_height * 10 + 1;
    for(int x = 0; x < maze_w; x++){
        if (x == 0 || x > 9){
            HSLAPixel & pixel = png_new -> getPixel(x, 0);
            pixel.l = 0;  
        }
    }
    for(int y = 0; y < maze_h; y++){
        HSLAPixel & pixel = png_new -> getPixel(0, y);
        pixel.l = 0;  
    }
    for(int x = 0; x < m_width; x++){
        for(int y = 0; y < m_height; y++){
            if(rht[y * m_width + x] == 1){
                for(int k = 0; k <= 10; k++){
                    HSLAPixel & pixel = png_new -> getPixel((x + 1) * 10, y * 10 + k);
                    pixel.l = 0;  
                }
            }
            if(dwn[y * m_width + x] == 1){
                for(int k = 0; k <= 10; k++){
                    HSLAPixel & pixel = png_new -> getPixel(x * 10 + k, (y + 1) * 10);
                    pixel.l = 0;  
                }
            }
        }
    }
    return png_new;
}






/**This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit
   Start at pixel (5,5). Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction.
   If the first step is downward, color pixels (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA). 
   Then if the second step is right, color pixels (5,15) through (15,15) red. 
   Then if the third step is up, color pixels (15,15) through (15,5) red. 
   Continue in this manner until you get to the end of the solution vector, 
   so that your output looks analogous the above picture.
   Make the exit by undoing the bottom wall of the destination square: 
   call the destination maze coordinates (x,y), and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9
   **/
PNG * SquareMaze::drawMazeWithSolution(){
    PNG* png_new = drawMaze();
    vector<int> result_vector = solveMaze();
    int x = 5;
    int y = x;
    
    int dest_x = dest % m_width;
    int dest_y = dest / m_height;

    for(int k = 1; k <= 9; k++){
        HSLAPixel& pixel = png_new -> getPixel(dest_x * 10 + k, (dest_y + 1) * 10);
        pixel.l = 1;
    }
    for(unsigned long i = 0; i < result_vector.size(); i++){
        if (result_vector[i] == 0){
            for(int k = 0; k <= 10; k++){
                HSLAPixel& pixel = png_new -> getPixel(x + k, y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            x = x + 10;
        }
        else if (result_vector[i] == 1){
            for(int k = 0; k <= 10; k++){
                HSLAPixel& pixel = png_new -> getPixel(x, y + k);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            } 
            y = y + 10;
        }
        else if (result_vector[i] == 2){
            for(int k = 0; k <= 10; k++){
                HSLAPixel& pixel = png_new -> getPixel(x - k, y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            x = x - 10;
        }
        else{       //result_vector[i] == 3
            for(int k = 0; k <= 10; k++){
                HSLAPixel& pixel = png_new -> getPixel(x, y - k);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            y = y - 10;
        }
    }
  return png_new;
}


