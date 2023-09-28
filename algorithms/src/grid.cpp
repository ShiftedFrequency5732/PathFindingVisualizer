#include "../include/grid.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

namespace Algorithms {
    using Constants::GAP_PX;

    Grid::Grid() {
        // At the start we do not have any start cell, nor the end cell.
        this->start_cell = this->end_cell = CellPoint(-1, -1);

        // At the start won't offset the world screen.
        this->offset = { 0.0f, 0.0f };

        // At the start, our world will have scale of 1.0.
        this->scale = { 1.0f, 1.0f };
    }

    void Grid::SetCellSize(int cell_size) {
        this->cell_size = cell_size;
    }

    void Grid::SetWindowSize(int window_width, int window_height) {
        this->window_width = window_width;
        this->window_height = window_height;
    }

    CellPoint Grid::GetStartCellPoint() const {
        return this->start_cell;
    }

    CellPoint Grid::GetEndCellPoint() const {
        return this->end_cell;
    }

    Cell& Grid::GetCell(int i, int j) {
        return this->matrix[i][j];
    }

    static bool in_bounds(Vector2 pos, int x_min, int x_max, int y_min, int y_max) {
        // Check if vector is in the proper bounds. This will be used to check if the mouse position is in the bounds of the window.
        return (pos.x >= x_min && pos.x <= x_max && pos.y >= y_min && pos.y <= y_max);
    }

    void Grid::Draw() {
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                // Turn the world position of cell into the screen space, include the grid gap in the calculation, as we want gap between the cells.
                Vector2 pos = WorldToScreen({ (float) (j * this->cell_size + GAP_PX), (float) (i * this->cell_size + GAP_PX) });

                if (in_bounds(pos, -this->cell_size * scale.x, window_width, -this->cell_size * scale.y, window_height)) {
                    // Draw the cell, only if its world position in the screen domain is in the bounds of the window that we are drawing on.
                    // We are checking pos.x >= -cell_size * scale.x and same for pos.y, because if pos.x = -cell_size * scale.x + n, that means we would see n pixel(s) of this cell.
                    // Also take into account gap size when drawing the cell of the size cell width, as we want to have gap around all sides of the cell, not just the top left corner.
                    DrawRectangle(pos.x, pos.y, (this->cell_size - GAP_PX) * this->scale.x, (this->cell_size - GAP_PX) * this->scale.y, matrix[i][j].GetFillColor());
                }
            }
        }
    }

    void Grid::MouseSetStartOrEndCell() {
        if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_E)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            // Take the current position of the mouse (that is in the screen domain), and turn it into the world domain
            Vector2 curr_scr = Vector2({ (float) GetMouseX(), (float) GetMouseY() });
            Vector2 top_left = WorldToScreen({ (float)0, (float)0 });
            Vector2 bottom_right = WorldToScreen({ (float) GRID_SIZE * this->cell_size + GAP_PX, (float) GRID_SIZE * this->cell_size + GAP_PX });

            if (in_bounds(curr_scr, top_left.x, bottom_right.x, top_left.y, bottom_right.y)) {
                Vector2 curr_wld = ScreenToWorld(curr_scr);
                // Map the mouse position to the cell of the matrix.
                int new_i = curr_wld.y / this->cell_size;
                int new_j = curr_wld.x / this->cell_size;

                if (matrix[new_i][new_j].GetType() == Cell::CellType::EMPTY) {
                    // If the user is holding S, the cell that we will work with is start, otherwise he is holding E and then we will work with the end cell.
                    Cell::CellType type = IsKeyDown(KEY_S) ? Cell::CellType::START : Cell::CellType::END;
                    CellPoint& ref_cell = IsKeyDown(KEY_S) ? start_cell : end_cell;

                    if (ref_cell.IsValid()) {
                        // In case we set the start or the end cell in the past remove it. We want to have only one start and the end cell.
                        matrix[ref_cell.I()][ref_cell.J()].SetType(Cell::CellType::EMPTY);
                    }

                    // Remember the new position of the cell, and set its type in the matrix.
                    ref_cell = CellPoint(new_i, new_j);
                    matrix[new_i][new_j].SetType(type);
                }
            }
        }
    }

    void Grid::MouseSetWallsOrEmptyCells() {
        if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_N)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            // If the user is holding W, we will place walls on the empty cells, otherwise we will place empty cells on the wall cells.
            Cell::CellType place_type = IsKeyDown(KEY_W) ? Cell::CellType::WALL : Cell::CellType::EMPTY;
            Cell::CellType on_the_type = (place_type == Cell::CellType::WALL) ? Cell::CellType::EMPTY : Cell::CellType::WALL;

            // Remember the previous mouse position as well as the current one. We want to fill all the cells in between these two positions in the world domain, so that we get the continuous line.
            // At one frame (one iteration of the game loop), the mouse could be at (0, 0), and on another at the (100, 100), due to the target FPS, and that is why we are doing this.
            this->mouse_prev = mouse_curr;
            this->mouse_curr = { (float) GetMouseX(), (float) GetMouseY() };

            // Convert the two previous positions into the world domain.
            this->mouse_prev_wld = mouse_curr_wld;
            this->mouse_curr_wld = ScreenToWorld(mouse_curr);
            if (this->mouse_prev_wld.x == -1 && this->mouse_prev_wld.y == -1) {
                // In case we do not have the previous mouse point, let it be equal to the current mouse point, that way it would seem as if we just made a click for start.
                this->mouse_prev_wld = mouse_curr_wld;
            }

            // Calculate 
            Vector2 top_left = WorldToScreen({ (float)0, (float)0 });
            Vector2 bottom_right = WorldToScreen({ (float) GRID_SIZE * this->cell_size + GAP_PX, (float) GRID_SIZE * this->cell_size + GAP_PX });

            if (in_bounds(mouse_curr, top_left.x, bottom_right.x, top_left.y, bottom_right.y) && in_bounds(mouse_prev, top_left.x, bottom_right.x, top_left.y, bottom_right.y)) {
                // Calculate the slope of the line between the previous and current mouse position.
                float x_distance = mouse_curr_wld.x - mouse_prev_wld.x;
                float y_distance = mouse_curr_wld.y - mouse_prev_wld.y;
                float slope = y_distance / x_distance;

                if (std::isnan(slope)) {
                    // If the slope is NaN, that means we divided zero with zero, the previous and the current mouse positions are equal. So we will place only one wall / empty cell.
                    int new_i = mouse_curr_wld.y / cell_size, new_j = mouse_curr_wld.x / cell_size;
                    if (matrix[new_i][new_j].GetType() == on_the_type) {
                        matrix[new_i][new_j].SetType(place_type);
                    }
                }
                else if (abs(x_distance) > abs(y_distance)) {
                    int x_min = std::min(mouse_prev_wld.x, mouse_curr_wld.x); 
                    int x_max = std::max(mouse_prev_wld.x, mouse_curr_wld.x);

                    // If the slope is in the range [-1, 1], we will use the y = slope * (x - x0) + y0, to find the y, and we will fill all the cells in between current and previous mouse postion.
                    for (int x = x_min; x <= x_max; ++x) {
                        int y = slope * (x - mouse_prev_wld.x) + mouse_prev_wld.y;
                        int new_i = y / cell_size, new_j = x / cell_size;
                        if (matrix[new_i][new_j].GetType() == on_the_type) {
                            matrix[new_i][new_j].SetType(place_type);
                        }
                    }
                }
                else {
                    int y_min = std::min(mouse_prev_wld.y, mouse_curr_wld.y);
                    int y_max = std::max(mouse_prev_wld.y, mouse_curr_wld.y);

                    // If the slope is not in the range [-1, 1], we will use x = (y - y0) / slope + x0, to find the x, and we will fill all the cells in between the current and previous mouse position.
                    for (int y = y_min; y <= y_max; ++y) {
                        int x = (y - mouse_prev_wld.y) / slope + mouse_prev_wld.x;
                        int new_i = y / cell_size, new_j = x / cell_size;
                        if (matrix[new_i][new_j].GetType() == on_the_type) {
                            matrix[new_i][new_j].SetType(place_type);
                        }
                    }
                 }
            }
        }
        else {
            // If the user didn't do anything, reset the previous and current mouse positions.
            this->mouse_prev = { -1, -1 };
            this->mouse_curr = { -1, -1 };
            this->mouse_prev_wld = { -1, -1 };
            this->mouse_curr_wld = { -1, -1 };
        }
    }

    Vector2 Grid::ScreenToWorld(Vector2 scr) {
        // We got this equation from the one below by moving around things around = operator in math.
        return { scr.x / scale.x + offset.x , scr.y / scale.y + offset.y };
    }

    Vector2 Grid::WorldToScreen(Vector2 wld) {
        // scr = (wld - offset) * scale (offset > 0, we move to the right, and things we see to the left, offset < 0, we move to the left, and things we see to the right). 
        return { (wld.x - offset.x) * scale.x, (wld.y - offset.y) * scale.y };
    }

    void Grid::MouseZoomAndPan() {
        Vector2 drag = { (float) GetMouseX(), (float) GetMouseY() };

        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            // Set the starting point from where we drag.
            this->start_pan = drag;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            // Calculate the distance between the starting point of when we pressed the mouse, and where we dragged the mouse, also apply the scaling on the distance, as we have zoom as well.
            // If the distance is positive, that means we want to drag the things we see to the right (In WldToScr -offset > 0), and therefore we want to move to the left (offset < 0)
            // If the distance is negative, that means we want to drag things we see to the left (In WldToScr -offset < 0), and therefore we want to move to the right (offset > 0).
            this->offset.x -= (drag.x - this->start_pan.x) / this->scale.x;
            this->offset.y -= (drag.y - this->start_pan.y) / this->scale.y;

            // Reset the starting point after applying the equations above, otherwise we will alter the offset indefinitely.
            this->start_pan = drag;
        }

        // Get the mouse position in the world domain, before zooming anything.
        Vector2 mouseBeforeZoom = ScreenToWorld(drag);

        float scroll = GetMouseWheelMove();
        if (scroll >= 0.5) {
            // If we are scrolling in the positive direction, increase the scale.
            scale = { scale.x * 1.1f, scale.y * 1.1f };
        }
        else if (scroll <= -0.5) {
            // If we are scrolling in the negative direction, decrease the scale.
            scale = { scale.x * .9f, scale.y * .9f };
        }

        // Get the mouse position in the world domain, after zooming things.
        Vector2 mouseAfterZoom = ScreenToWorld(drag);

        // If we increased our scale, the distance between the points became greater, as things became larger, therefore no_zoom(x, y) < zoom(x, y), offset has increased.
        // In order to keep the point around which we want to zoom the world, we need to take the difference between zoom(x, y) and no_zoom(x, y), and decrease the offset back by that.
        // If we decreased our scale, the distance became shorter, no_zoom(x, y) > unzoom(x, y), offset decreased, we need to increase it by the difference (that is now negative).
        this->offset.x -= (mouseAfterZoom.x - mouseBeforeZoom.x);
        this->offset.y -= (mouseAfterZoom.y - mouseBeforeZoom.y);
    }
}

