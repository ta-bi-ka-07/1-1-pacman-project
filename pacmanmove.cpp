// int isPacmanAlignedWithGrid() {
//     int cellwidth, cellheight;
    
//     if (level1page){
//         cellwidth = screenWidth / col1;
//         cellheight = screenHeight / row1;
//     } 
//     else if (level2page){
//         cellwidth = screenWidth / col2;
//         cellheight = screenHeight / row2;
//     }
//     else if (level3page){
//         cellwidth = screenWidth / col3;
//         cellheight = screenHeight / row3;
//     }
    
//     // Calculate what the centered position should be for current grid cell
//     int expectedX = pacmanCol * cellwidth + cellwidth/2;
//     int expectedY = screenHeight - (pacmanRow + 1) * cellheight + cellheight/2;
    
//     // Check if Pacman is close enough to the center (within a small tolerance)
//     int tolerance = pacmanSpeed; // Allow some tolerance based on movement speed
    
//     return (abs(pacmanPixelX - expectedX) <= tolerance && 
//             abs(pacmanPixelY - expectedY) <= tolerance);
// }

// //Aligns Pacman to the Grid Coordinates, helps with changing directions
// void alignPacmanToGrid() {
//     int cellwidth, cellheight;
    
//     if (level1page) {
//         cellwidth = screenWidth / col1;
//         cellheight = screenHeight / row1;
//     } else if (level2page) {
//         cellwidth = screenWidth / col2;
//         cellheight = screenHeight / row2;
//     } else if (level3page) {
//         cellwidth = screenWidth / col3;
//         cellheight = screenHeight / row3;
//     }
    
//     if (level1page || level2page){
//         pacmanPixelX = pacmanCol*cellwidth + 8;
//         pacmanPixelY = screenHeight-(pacmanRow+1)*cellheight + 8;
//     }
//     else{
//         pacmanPixelX = pacmanCol*cellwidth + 5;
//         pacmanPixelY = screenHeight-(pacmanRow+1)*cellheight + 5;
//     }

// }

// // Give Pixel Coordinates to turn into Grid Position (Row and Column)
// void getGridPosition(int pixelX, int pixelY, int* row, int* col){
//     if (level1page){
//         cellwidth = screenWidth / col1;
//         cellheight = screenHeight / row1;
        
//         *col = pixelX / cellwidth;
//         *row = (screenHeight - pixelY) / cellheight;
        
//         // Clamp to valid range
//         if (*row < 0) *row = 0;
//         if (*row >= row1) *row = row1 - 1;
//         if (*col < 0) *col = 0;
//         if (*col >= col1) *col = col1 - 1;
//     }
//     else if (level2page){
//         cellwidth = screenWidth / col2;
//         cellheight = screenHeight / row2;
        
//         *col = pixelX / cellwidth;
//         *row = (screenHeight - pixelY) / cellheight;
        
//         // Clamp to valid range
//         if (*row < 0) *row = 0;
//         if (*row >= row2) *row = row2 - 1;
//         if (*col < 0) *col = 0;
//         if (*col >= col2) *col = col2 - 1;
//     }
//     else if (level3page){
//         cellwidth = screenWidth / col3;
//         cellheight = screenHeight / row3;
        
//         *col = pixelX / cellwidth;
//         *row = (screenHeight - pixelY) / cellheight;
        
//         // Clamp to valid range
//         if (*row < 0) *row = 0;
//         if (*row >= row3) *row = row3 - 1;
//         if (*col < 0) *col = 0;
//         if (*col >= col3) *col = col3 - 1;
//     }
// }

// int isValidPosition(int row, int col){
//    if (level1page){
//         if (row < 0 || row >= row1 || col < 0 || col >= col1){
//             return 0;
//         }
//         return maze1[row][col] != 1;
//    }
//    if (level2page){
//         if (row < 0 || row >= row2 || col < 0 || col >= col2){
//             return 0;
//         }
//         return maze2[row][col] != 1;
//    }
//    if (level3page){
//         if (row < 0 || row >= row3 || col < 0 || col >= col3){
//             return 0;
//         }
//         return maze3[row][col] != 1;
//    }
// }

// int canMoveInDirection(int direction) {
//     int newRow = pacmanRow;
//     int newCol = pacmanCol;
    
//     switch (direction) {
//         case Left:  newCol--; break;
//         case Right: newCol++; break;
//         case Up:    newRow--; break;
//         case Down:  newRow++; break;
//     }
    
//     return isValidPosition(newRow, newCol);
// }


// void startMoving(int direction) {
//     if (canStartMoving(direction)) {
//         pacmanDirection = direction;
//         isMoving = 1;

//         if (level1page) {
//             cellwidth = screenWidth / col1;
//             cellheight = screenHeight / row1;
//         } else if (level2page) {
//             cellwidth = screenWidth / col2;
//             cellheight = screenHeight / row2;
//         } else if (level3page) {
//             cellwidth = screenWidth / col3;
//             cellheight = screenHeight / row3;
//         }
        
//         int newTargetX = pacmanPixelX;
//         int newTargetY = pacmanPixelY;
        
//         switch (direction) {
//             case Left:
//                 newTargetX -= cellwidth;
//                 break;
//             case Right:
//                 newTargetX += cellwidth;
//                 break;
//             case Up:
//                 newTargetY += cellheight;
//                 break;
//             case Down:
//                 newTargetY -= cellheight;
//                 break;
//         }
        
//         if (isPixelPositionValid(newTargetX, newTargetY)) {
//             targetPixelX = newTargetX;
//             targetPixelY = newTargetY;
//         } else {
//             isMoving = 0;
//         }
//     }

// }

// //Turns Pixel Coordinates into Grid Coordinates and checks if they're valid
// int isPixelPositionValid(int pixelX, int pixelY) {
//     int row, col;
//     getGridPosition(pixelX, pixelY, &row, &col);
//     return isValidPosition(row, col);
// }

// int canStartMoving(int direction) {
//     if (!isPacmanAlignedWithGrid()) {
//         alignPacmanToGrid();
//     }
    
//     return canMoveInDirection(direction);
// }

// void updatePacmanMovement() {
//     if (!isMoving) {
//         // Not moving, check if we should continue in current direction
//         if (canMoveInDirection(pacmanDirection)) {
//             startMoving(pacmanDirection);
//         }
//         return;
//     }
    
//     // Calculate distance to target
//     int distanceX = targetPixelX - pacmanPixelX;
//     int distanceY = targetPixelY - pacmanPixelY;
//     int distance = abs(distanceX) + abs(distanceY);
    
//     // If we're close enough to target, snap to it
//     if (distance <= pacmanSpeed) {
//         // Before snapping, verify the target position is still valid
//         if (isPixelPositionValid(targetPixelX, targetPixelY)) {
//             pacmanPixelX = targetPixelX;
//             pacmanPixelY = targetPixelY;
//             isMoving = 0; //Keeps moving in that direction until change
            
//             // Update grid position
//             getGridPosition(pacmanPixelX, pacmanPixelY, &pacmanRow, &pacmanCol);
            
//             // Eat food/pellets at new position
//             if (level1page) {
//                 if (maze1[pacmanRow][pacmanCol] == 2) {
//                     maze1[pacmanRow][pacmanCol] = -1;  // Remove power pellet
//                 } else if (maze1[pacmanRow][pacmanCol] == 0) {
//                     maze1[pacmanRow][pacmanCol] = -1;  // Remove dot
//                 }
//             }
//             else if (level2page) {
//                 if (maze2[pacmanRow][pacmanCol] == 2) {
//                     maze2[pacmanRow][pacmanCol] = -1;  // Remove power pellet
//                 } else if (maze2[pacmanRow][pacmanCol] == 0) {
//                     maze2[pacmanRow][pacmanCol] = -1;  // Remove dot
//                 }
//             }
//             else if (level3page) {
//                 if (maze3[pacmanRow][pacmanCol] == 2) {
//                     maze3[pacmanRow][pacmanCol] = -1;  // Remove power pellet
//                 } else if (maze3[pacmanRow][pacmanCol] == 0) {
//                     maze3[pacmanRow][pacmanCol] = -1;  // Remove dot
//                 }
//             }
//             // Check for pending direction changes
//             if (pendingDirection != -1 && canMoveInDirection(pendingDirection)) {
//                 pacmanDirection = pendingDirection;
//                 startMoving(pendingDirection);
//                 pendingDirection = -1;
//             }
//             // Otherwise continue in current direction if possible
//             else if (canMoveInDirection(pacmanDirection)) {
//                 startMoving(pacmanDirection);
//             }
//             else {
//             // Target position became invalid, stop and align
//             isMoving = 0;
//             alignPacmanToGrid();
//             }
//             }
//         }    
//         else {
//         // Calculate next position with smaller steps for better collision detection
//         int stepSize = min(pacmanSpeed, distance);
//         int nextX = pacmanPixelX;
//         int nextY = pacmanPixelY;
        
//         // Move in smaller increments to avoid skipping through walls
//         if (distanceX > 0) nextX += min(stepSize, distanceX);
//         else if (distanceX < 0) nextX += max(-stepSize, distanceX);
        
//         if (distanceY > 0) nextY += min(stepSize, distanceY);
//         else if (distanceY < 0) nextY += max(-stepSize, distanceY);
        
//         // Validate the next position before moving
//         if (isPixelPositionValid(nextX, nextY)) {
//             pacmanPixelX = nextX;
//             pacmanPixelY = nextY;
//         } else {
//             // Hit a wall, stop moving and align to grid
//             isMoving = 0;
//             alignPacmanToGrid();
//             }
//         }
// }
