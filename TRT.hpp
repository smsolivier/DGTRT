#pragma once

#include "Error.hpp"
#include "Array.hpp"
#include "Quadrature.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Basis.hpp"
#include "BilinearIntegrator.hpp"
#include "LinearIntegrator.hpp"
#include "Element.hpp"
#include "ElTrans.hpp"
#include "FESpace.hpp"
#include "L2Segment.hpp"
#include "Node.hpp"
#include "Coefficient.hpp"
#include "Sweeper.hpp"
#include "TransportOperator.hpp"
#include "TVector.hpp"
#include "WallTimer.hpp"
#include "Lua.hpp"
#include "GridFunction.hpp"
#include "Writer.hpp"
#include "Opacity.hpp"
#include "Timer.hpp"

// start the wall timer 
static trt::WallTimer& wt = trt::WallTimer::instance(); 
