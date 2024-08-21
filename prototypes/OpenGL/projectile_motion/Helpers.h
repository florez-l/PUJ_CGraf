// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __Helpers__h__
#define __Helpers__h__

/**
 */
template< class _TReal >
void multiply_4x4(
  _TReal& ox, _TReal& oy, _TReal& oz,
  const _TReal* mat,
  const _TReal& ix, const _TReal& iy, const _TReal& iz
  )
{
  ox = ( mat[ 0 ] * ix ) + ( mat[ 4 ] * iy ) + ( mat[ 8 ] * iz ) + mat[ 12 ];
  oy = ( mat[ 1 ] * ix ) + ( mat[ 5 ] * iy ) + ( mat[ 9 ] * iz ) + mat[ 13 ];
  oz = ( mat[ 2 ] * ix ) + ( mat[ 6 ] * iy ) + ( mat[ 7 ] * iz ) + mat[ 14 ];
}

/**
 */
template< class _TReal >
bool invert_matrix_4x4( const _TReal* mat, _TReal* inv )
{
  inv[ 0 ] =
    ( mat[  5 ] * mat[ 10 ] * mat[ 15 ] ) -
    ( mat[  5 ] * mat[ 11 ] * mat[ 14 ] ) -
    ( mat[  9 ] * mat[  6 ] * mat[ 15 ] ) +
    ( mat[  9 ] * mat[  7 ] * mat[ 14 ] ) +
    ( mat[ 13 ] * mat[  6 ] * mat[ 11 ] ) -
    ( mat[ 13 ] * mat[  7 ] * mat[ 10 ] );

  inv[ 4 ] =
    ( -mat[  4 ] * mat[ 10 ] * mat[ 15 ] ) +
    (  mat[  4 ] * mat[ 11 ] * mat[ 14 ] ) +
    (  mat[  8 ] * mat[  6 ] * mat[ 15 ] ) -
    (  mat[  8 ] * mat[  7 ] * mat[ 14 ] ) -
    (  mat[ 12 ] * mat[  6 ] * mat[ 11 ] ) +
    (  mat[ 12 ] * mat[  7 ] * mat[ 10 ] );

  inv[ 8 ] =
    ( mat[  4 ] * mat[  9 ] * mat[ 15 ] ) -
    ( mat[  4 ] * mat[ 11 ] * mat[ 13 ] ) -
    ( mat[  8 ] * mat[  5 ] * mat[ 15 ] ) +
    ( mat[  8 ] * mat[  7 ] * mat[ 13 ] ) +
    ( mat[ 12 ] * mat[  5 ] * mat[ 11 ] ) -
    ( mat[ 12 ] * mat[  7 ] * mat[  9 ] );

  inv[ 12 ] =
    ( -mat[  4 ] * mat[  9 ] * mat[ 14 ] ) +
    (  mat[  4 ] * mat[ 10 ] * mat[ 13 ] ) +
    (  mat[  8 ] * mat[  5 ] * mat[ 14 ] ) -
    (  mat[  8 ] * mat[  6 ] * mat[ 13 ] ) -
    (  mat[ 12 ] * mat[  5 ] * mat[ 10 ] ) +
    (  mat[ 12 ] * mat[  6 ] * mat[  9 ] );

  inv[ 1 ] =
    ( -mat[  1 ] * mat[ 10 ] * mat[ 15 ] ) +
    (  mat[  1 ] * mat[ 11 ] * mat[ 14 ] ) +
    (  mat[  9 ] * mat[  2 ] * mat[ 15 ] ) -
    (  mat[  9 ] * mat[  3 ] * mat[ 14 ] ) -
    (  mat[ 13 ] * mat[  2 ] * mat[ 11 ] ) +
    (  mat[ 13 ] * mat[  3 ] * mat[ 10 ] );

  inv[ 5 ] =
    ( mat[  0 ] * mat[ 10 ] * mat[ 15 ] ) -
    ( mat[  0 ] * mat[ 11 ] * mat[ 14 ] ) -
    ( mat[  8 ] * mat[  2 ] * mat[ 15 ] ) +
    ( mat[  8 ] * mat[  3 ] * mat[ 14 ] ) +
    ( mat[ 12 ] * mat[  2 ] * mat[ 11 ] ) -
    ( mat[ 12 ] * mat[  3 ] * mat[ 10 ] );

  inv[ 9 ] =
    ( -mat[  0 ] * mat[  9 ] * mat[ 15 ] ) +
    (  mat[  0 ] * mat[ 11 ] * mat[ 13 ] ) +
    (  mat[  8 ] * mat[  1 ] * mat[ 15 ] ) -
    (  mat[  8 ] * mat[  3 ] * mat[ 13 ] ) -
    (  mat[ 12 ] * mat[  1 ] * mat[ 11 ] ) +
    (  mat[ 12 ] * mat[  3 ] * mat[  9 ] );

  inv[ 13 ] =
    ( mat[  0 ] * mat[  9 ] * mat[ 14 ] ) -
    ( mat[  0 ] * mat[ 10 ] * mat[ 13 ] ) -
    ( mat[  8 ] * mat[  1 ] * mat[ 14 ] ) +
    ( mat[  8 ] * mat[  2 ] * mat[ 13 ] ) +
    ( mat[ 12 ] * mat[  1 ] * mat[ 10 ] ) -
    ( mat[ 12 ] * mat[  2 ] * mat[  9 ] );

  inv[ 2 ] =
    ( mat[  1 ] * mat[ 6 ] * mat[ 15 ] ) -
    ( mat[  1 ] * mat[ 7 ] * mat[ 14 ] ) -
    ( mat[  5 ] * mat[ 2 ] * mat[ 15 ] ) +
    ( mat[  5 ] * mat[ 3 ] * mat[ 14 ] ) +
    ( mat[ 13 ] * mat[ 2 ] * mat[  7 ] ) -
    ( mat[ 13 ] * mat[ 3 ] * mat[  6 ] );

  inv[ 6 ] =
    ( -mat[  0 ] * mat[ 6 ] * mat[ 15 ] ) +
    (  mat[  0 ] * mat[ 7 ] * mat[ 14 ] ) +
    (  mat[  4 ] * mat[ 2 ] * mat[ 15 ] ) -
    (  mat[  4 ] * mat[ 3 ] * mat[ 14 ] ) -
    (  mat[ 12 ] * mat[ 2 ] * mat[  7 ] ) +
    (  mat[ 12 ] * mat[ 3 ] * mat[  6 ] );

  inv[ 10 ] =
    ( mat[  0 ] * mat[ 5 ] * mat[ 15 ] ) -
    ( mat[  0 ] * mat[ 7 ] * mat[ 13 ] ) -
    ( mat[  4 ] * mat[ 1 ] * mat[ 15 ] ) +
    ( mat[  4 ] * mat[ 3 ] * mat[ 13 ] ) +
    ( mat[ 12 ] * mat[ 1 ] * mat[  7 ] ) -
    ( mat[ 12 ] * mat[ 3 ] * mat[  5 ] );

  inv[ 14 ] =
    ( -mat[  0 ] * mat[ 5 ] * mat[ 14 ] ) +
    (  mat[  0 ] * mat[ 6 ] * mat[ 13 ] ) +
    (  mat[  4 ] * mat[ 1 ] * mat[ 14 ] ) -
    (  mat[  4 ] * mat[ 2 ] * mat[ 13 ] ) -
    (  mat[ 12 ] * mat[ 1 ] * mat[  6 ] ) +
    (  mat[ 12 ] * mat[ 2 ] * mat[  5 ] );

  inv[ 3 ] =
    ( -mat[ 1 ] * mat[ 6 ] * mat[ 11 ] ) +
    (  mat[ 1 ] * mat[ 7 ] * mat[ 10 ] ) +
    (  mat[ 5 ] * mat[ 2 ] * mat[ 11 ] ) -
    (  mat[ 5 ] * mat[ 3 ] * mat[ 10 ] ) -
    (  mat[ 9 ] * mat[ 2 ] * mat[  7 ] ) +
    (  mat[ 9 ] * mat[ 3 ] * mat[  6 ] );

  inv[ 7 ] =
    ( mat[ 0 ] * mat[ 6 ] * mat[ 11 ] ) -
    ( mat[ 0 ] * mat[ 7 ] * mat[ 10 ] ) -
    ( mat[ 4 ] * mat[ 2 ] * mat[ 11 ] ) +
    ( mat[ 4 ] * mat[ 3 ] * mat[ 10 ] ) +
    ( mat[ 8 ] * mat[ 2 ] * mat[  7 ] ) -
    ( mat[ 8 ] * mat[ 3 ] * mat[  6 ] );

  inv[ 11 ] =
    ( -mat[ 0 ] * mat[ 5 ] * mat[ 11 ] ) +
    (  mat[ 0 ] * mat[ 7 ] * mat[  9 ] ) +
    (  mat[ 4 ] * mat[ 1 ] * mat[ 11 ] ) -
    (  mat[ 4 ] * mat[ 3 ] * mat[  9 ] ) -
    (  mat[ 8 ] * mat[ 1 ] * mat[  7 ] ) +
    (  mat[ 8 ] * mat[ 3 ] * mat[  5 ] );

  inv[ 15 ] =
    ( mat[ 0 ] * mat[ 5 ] * mat[ 10 ] ) -
    ( mat[ 0 ] * mat[ 6 ] * mat[  9 ] ) -
    ( mat[ 4 ] * mat[ 1 ] * mat[ 10 ] ) +
    ( mat[ 4 ] * mat[ 2 ] * mat[  9 ] ) +
    ( mat[ 8 ] * mat[ 1 ] * mat[  6 ] ) -
    ( mat[ 8 ] * mat[ 2 ] * mat[  5 ] );

  _TReal det =
    ( mat[ 0 ] * inv[  0 ] ) +
    ( mat[ 1 ] * inv[  4 ] ) +
    ( mat[ 2 ] * inv[  8 ] ) +
    ( mat[ 3 ] * inv[ 12 ] );

  if( det == _TReal( 0 ) )
    return( false );
  det = _TReal( 1 ) / det;

  for( int i = 0; i < 16; i++ )
    inv[ i ] *= det;

  return( true );
}

#endif // __Helpers__h__

// eof - $RCSfile$
