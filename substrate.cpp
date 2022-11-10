/*
 * File:	substrate.cpp
 * Author:	Stanley Goodwin
 * Stores the simulation's substrate characteristics.
 */
#include <math.h>
#include "substrate.hpp"

/*
 * Definition of constructing a surface object.
 * @brief	Surface contructor definition.
 * @param	_printed_receding_angle     double
 * @param	_printed_receding_width     double
 * @param	_unprinted_receding_angle   double
 * @param	_unprinted_receding_width   double
 */
Substrate::Substrate(
    double _printed_receding_angle, 
    double _printed_receding_width, 
    double _unprinted_receding_angle, 
    double _unprinted_receding_width
) {
    printed_receding_angle = _printed_receding_angle;
    printed_receding_width = _printed_receding_width;
    unprinted_receding_angle = _unprinted_receding_angle;
    unprinted_receding_width = _unprinted_receding_width;
    kp = 1.0 / tan(printed_receding_angle);
    kg = 1.0 / tan(unprinted_receding_angle);
}

/*
 * Tests if node is on the printed region and slips.
 * @brief	Node slip function.
 * @param	_node            Node    The node that may be slipping.
 * @param	_contact_angle   double  The node's surface contact angle with the plane.
 */
bool Substrate::slips_on_printed(Node _node, double _contact_angle)
{
    // Tests if the contact angle is large enough to not slip
    if (_contact_angle >= printed_receding_angle)
        return false;

    // Declare variable values
    double abs_y_val = fabs(_node.y) - 0.5 * printed_receding_width;

    // Region booleans
    bool r1 = (       -0.5 * printed_receding_width <= abs_y_val && abs_y_val <= 0 * unprinted_receding_width + 0 * printed_receding_width);
    bool r2 = (1 * unprinted_receding_width + 0 * printed_receding_width <= abs_y_val && abs_y_val <= 1 * unprinted_receding_width + 1 * printed_receding_width);

    // Return true if point is on printed region, else false
    return r1 || r2;
}

/*
 * Tests if node is on the unprinted region and slips.
 * @brief	Node slip function.
 * @param	_node            Node    The node that may be slipping.
 * @param	_contact_angle   double  The node's surface contact angle with the plane.
 */
bool Substrate::slips_on_unprinted(Node _node, double _contact_angle)
{
    // Tests if the contact angle is large enough to not slip
    if (_contact_angle >= unprinted_receding_angle)
        return false;
    
    // Declare variable values
    double abs_y_val = fabs(_node.y) - 0.5 * printed_receding_width;

    // Region booleans
    bool r1 = (       -0.5 * printed_receding_width <= abs_y_val && abs_y_val <= 0 * unprinted_receding_width + 0 * printed_receding_width);
    bool r2 = (1 * unprinted_receding_width + 0 * printed_receding_width <= abs_y_val && abs_y_val <= 1 * unprinted_receding_width + 1 * printed_receding_width);

    // Return true if point is on non-printed region, else false
    return !(r1 || r2);
}