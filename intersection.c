/* =============================================================== */

/* This function was adapted by Alistair Moffat in 2012 from 
 * http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/pdb.c
 * (no longer available at that URL in 2013)
 * and was written in the first instance by Paul Bourke
 *
 * Modified for use in a different assignment previously  by:
 *   . changing the argument type to two structs type line_t
 *   . making sure result is TRUE if an endpoint is on the other line
 */
#define TRUE 1
#define FALSE 0
#define EPS (1e-06)
#define ABS(x) (fabs(x))

int lineIntersect(line_t l1, line_t l2) {
   double x1=l1.p1.x, y1=l1.p1.y,
   	  x2=l1.p2.x, y2=l1.p2.y,
   	  x3=l2.p1.x, y3=l2.p1.y,
   	  x4=l2.p2.x, y4=l2.p2.y;
   double mua,mub;
   double denom,numera,numerb;

   denom  = (y4-y3) * (x2-x1) - (x4-x3) * (y2-y1);
   numera = (x4-x3) * (y1-y3) - (y4-y3) * (x1-x3);
   numerb = (x2-x1) * (y1-y3) - (y2-y1) * (x1-x3);

   /* Are the line coincident? */
   if (ABS(numera) < EPS && ABS(numerb) < EPS && ABS(denom) < EPS) {
      return(TRUE);
   }

   /* Are the line parallel */
   if (ABS(denom) < EPS) {
      return(FALSE);
   }

   /* Is the intersection along the the segments */
   mua = numera / denom;
   mub = numerb / denom;
   /* AM - use equality here so that "on the end" is not an
    * intersection; use strict inequality if "touching at end" is an
    * intersection */
   if (mua < 0 || mua > 1 || mub < 0 || mub > 1) {
      return(FALSE);
   }
   return(TRUE);
}
