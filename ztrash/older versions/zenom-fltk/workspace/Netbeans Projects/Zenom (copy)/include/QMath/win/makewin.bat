cd ..
cl /c /EHsc /O2 Transform.cpp
cl /c /EHsc /O2 GSLCompat.cpp /I ./win/WinGsl
link -lib /out:"QMath.lib" Transform.obj GSLCompat.obj
del *.obj
move QMath.lib win
cd examples
cl /EHsc /O2 Adams3Integrator.t.cpp /I ../ /link ../win/QMath.lib
cl /EHsc /O2 Differentiator.t.cpp /I ../ /link ../win/QMath.lib
cl /EHsc /O2 Differentiator4O.t.cpp /I ../ /link ../win/QMath.lib
cl /EHsc /O2 HighpassFilter.t.cpp /I ../ /link ../win/QMath.lib
cl /EHsc /O2 Integrator.t.cpp /I ../ /link ../win/QMath.lib
cl /EHsc /O2 LowpassFilter.t.cpp /I ../ /link ../win/QMath.lib
cl /EHsc /O2 MathException.t.cpp /I ../ /link ../win/QMath.lib
cl /EHsc /O2 Matrix.t.cpp /I ../ /link ../win/QMath.lib
cl /EHsc /O2 ODESolverRK4.t.cpp /I ../ /link ../win/QMath.lib
cl /EHsc /O2 Transform.t.cpp /I ../ /link ../win/QMath.lib
cl /EHsc /O2 Vector.t.cpp /I ../ /link ../win/QMath.lib
cl /EHsc /O2 GSLCompat.t.cpp /I ../ /I ../win/WinGsl /link ../win/QMath.lib ../win/WinGsl/lib/WinGsl.lib
del *.obj
move *.exe ../win
cd ../win