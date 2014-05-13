program laplsolv
use omp_lib
!-----------------------------------------------------------------------
! Serial program for solving the heat conduction problem 
! on a square using the Jacobi method. 
! Written by Fredrik Berntsson (frber@math.liu.se) March 2003
! Modified by Berkant Savas (besav@math.liu.se) April 2006
!-----------------------------------------------------------------------
  integer, parameter                  :: n=1000, maxiter=1000
  double precision,parameter          :: tol=1.0E-3
  double precision,dimension(0:n+1,0:n+1) :: T
  double precision,dimension(n)       :: tmp_left,tmp_mid,tmp_right,tmp_last
  double precision                    :: error,x
  double precision                    :: t1,t0
  integer                             :: j,k, num_threads
  integer                             :: myid, team_size, even_cols, my_cols
  character(len=20)                   :: str, arg
  
  ! Set boundary conditions and initial values for the unknowns
  T=0.0D0
  T(0:n+1 , 0)     = 1.0D0
  T(0:n+1 , n+1)   = 1.0D0
  T(n+1   , 0:n+1) = 2.0D0
  
  call getarg(1, arg)
  read(arg, '(i10)' ) num_threads
  call omp_set_num_threads(num_threads)

  ! Solve the linear system of equations using the Jacobi method
  t0 = omp_get_wtime()

  do k=1,maxiter
     
     error=0.0D0
     !$OMP parallel default(private) shared(T,k) reduction(max:error)
     myid = omp_get_thread_num()
     team_size = omp_get_num_threads()
     even_cols = n/team_size;

     tmp_left=T(1:n,myid*even_cols)

     if(myid == team_size-1) then
        tmp_last=T(1:n,n+1)
        my_cols = even_cols + mod(n, team_size)
     else 
        my_cols = even_cols
        tmp_last = T(1:n,(myid+1)*even_cols+1)
     end if

     !$OMP BARRIER
     do j=myid*even_cols+1,myid*even_cols+my_cols

        tmp_mid=T(1:n,j)
        if(j == (myid+1)*my_cols) then
          tmp_right = tmp_last
        else
          tmp_right=T(1:n,j+1)
        end if
        T(1:n,j)=(T(0:n-1,j)+T(2:n+1,j)+tmp_right+tmp_left)/4.0D0
        error=max(error,maxval(abs(tmp_mid-T(1:n,j))))
        tmp_left=tmp_mid
     end do
     !$OMP end parallel
     
     if (error<tol) then
        exit
     end if
     
  end do
  
  t1 = omp_get_wtime()

  write(unit=*,fmt=*) 'Time:',t1-t0,'Number of Iterations:',k
  write(unit=*,fmt=*) 'Temperature of element T(1,1)  =',T(1,1)
  write(unit=*,fmt=*) 'Error =',error

  ! Uncomment the next part if you want to write the whole solution
  ! to a file. Useful for plotting. 
  
  !open(unit=7,action='write',file='result.dat',status='unknown')
  !write(unit=str,fmt='(a,i6,a)') '(',N,'F10.6)'
  !do i=0,n+1
  !   write (unit=7,fmt=str) T(i,0:n+1)  
  !end do
  !close(unit=7)
  
end program laplsolv
