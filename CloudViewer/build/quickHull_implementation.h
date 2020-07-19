#pragma once
// A divide and conquer program to find convex 
// hull of a given set of points. 
#include<iostream> 
#include<vector>
#include <set>
#include <algorithm>    // std::sort
using namespace std;

/*
---------------------------------------------algorithm-------------------------------------
Find the point with minimum x-coordinate lets say, min_x and similarly the point with maximum x-coordinate, max_x.
Make a line joining these two points, say L. This line will divide the whole set into two parts. Take both the parts one by one and proceed further.
For a part, find the point P with maximum distance from the line L. P forms a triangle with the points min_x, max_x. It is clear that the points residing inside this triangle can never be the part of convex hull.
The above step divides the problem into two sub-problems (solved recursively). Now the line joining the points P and min_x and the line joining the points P and max_x are new lines and the points residing outside the triangle is the set of points. Repeat point no.
3 till there no point left with the line. Add the end points of this point to the convex hull.

*/
// iPair is integer pairs 
#define iPair pair<int, int> 

// Stores the result (points of convex hull) 
set<iPair> hull;


// Returns the side of point p with respect to line 
// joining points p1 and p2. 
int findSide(iPair p1, iPair p2, iPair p)
{
    int val = (p.second - p1.second) * (p2.first - p1.first) -
        (p2.second - p1.second) * (p.first - p1.first);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

// returns a value proportional to the distance 
// between the point p and the line joining the 
// points p1 and p2 
int lineDist(iPair p1, iPair p2, iPair p)
{
    return abs((p.second - p1.second) * (p2.first - p1.first) -
        (p2.second - p1.second) * (p.first - p1.first));
}

// End points of line L are p1 and p2.  side can have value 
// 1 or -1 specifying each of the parts made by the line L 
void quickHull(vector<iPair> a, int n, iPair p1, iPair p2, int side)
{
    int ind = -1;
    int max_dist = 0;

    // finding the point with maximum distance 
    // from L and also on the specified side of L. 
    for (int i = 0; i < n; i++)
    {
        int temp = lineDist(p1, p2, a[i]);
        if (findSide(p1, p2, a[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }

    // If no point is found, add the end points 
    // of L to the convex hull. 
    if (ind == -1)
    {
        hull.insert(p1);
        hull.insert(p2);
        return;
    }

    // Recur for the two parts divided by a[ind] 
    quickHull(a, n, a[ind], p1, -findSide(a[ind], p1, p2));
    quickHull(a, n, a[ind], p2, -findSide(a[ind], p2, p1));
}

void printHull(vector<iPair> a, int n)
{
    // a[i].second -> y-coordinate of the ith point 
    if (n < 3)
    {
        cout << "Convex hull not possible\n";
        return;
    }

    // Finding the point with minimum and 
    // maximum x-coordinate 
    int min_x = 0, max_x = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i].first < a[min_x].first)
            min_x = i;
        if (a[i].first > a[max_x].first)
            max_x = i;
    }

    // Recursively find convex hull points on 
    // one side of line joining a[min_x] and 
    // a[max_x] 
    quickHull(a, n, a[min_x], a[max_x], 1);

    // Recursively find convex hull points on 
    // other side of line joining a[min_x] and 
    // a[max_x] 
    quickHull(a, n, a[min_x], a[max_x], -1);

    cout << "The points in Convex Hull are:\n";
    while (!hull.empty())
    {
        cout << "(" << (*hull.begin()).first << ", "
            << (*hull.begin()).second << ") ";
        hull.erase(hull.begin());
    }
}