************************************************************************
*                                                                      *
      subroutine usrsors(x,y,z,u,v,w,e,wt,time,name,kf,nc1,nc2,nc3,
     &                   sx,sy,sz)
*                                                                      *
*        sample subroutine for user defined source.                    *
*                                                                      *
*        variables :                                                   *
*                                                                      *
*           x, y, z : position of the source.                          *
*           u, v, w : unit vector of the particle direction.           *
*           e       : kinetic energy of particle (MeV).                *
*           wt      : weight of particle.                              *
*           time    : initial time of particle. (ns)                   *
*           name    : usually = 1, for Coulmb spread.                  *
*           kf      : kf code of the particle.                         *
*           nc1     : initial value of counter 1                       *
*           nc2     : initial value of counter 2                       *
*           nc3     : initial value of counter 3                       *
*           sx,sy,sz : spin components                                 *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*        kf code table                                                 *
*                                                                      *
*           kf-code: ityp :  description                               *
*                                                                      *
*             2212 :   1  :  proton                                    *
*             2112 :   2  :  neutron                                   *
*              211 :   3  :  pion (+)                                  *
*              111 :   4  :  pion (0)                                  *
*             -211 :   5  :  pion (-)                                  *
*              -13 :   6  :  muon (+)                                  *
*               13 :   7  :  muon (-)                                  *
*              321 :   8  :  kaon (+)                                  *
*              311 :   9  :  kaon (0)                                  *
*             -321 :  10  :  kaon (-)                                  *
*                                                                      *
*           kf-code of the other transport particles                   *
*                                                                      *
*               12 :         nu_e                                      *
*               14 :         nu_mu                                     *
*              221 :         eta                                       *
*              331 :         eta'                                      *
*             -311 :         k0bar                                     *
*            -2112 :         nbar                                      *
*            -2212 :         pbar                                      *
*             3122 :         Lanbda0                                   *
*             3222 :         Sigma+                                    *
*             3212 :         Sigma0                                    *
*             3112 :         Sigma-                                    *
*             3322 :         Xi0                                       *
*             3312 :         Xi-                                       *
*             3334 :         Omega-                                    *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*        available function for random number                          *
*                                                                      *
*           unirn(dummy) : uniform random number from 0 to 1           *
*           gaurn(dummy) : gaussian random number                      *
*                          for exp( - x**2 / 2 / sig**2 ) : sig = 1.0  *
*                                                                      *
************************************************************************

      implicit real*8 (a-h,o-z)

*-----------------------------------------------------------------------

      parameter ( pi  = 3.141592653589793d0 )
      parameter(npart=33) ! number of applicable particle
      parameter(nebin=1000) ! number of energy mesh (divided by log)
      parameter(nabin=1000) ! number of angle mesh (divided by linear)
      dimension IangPart(0:npart)
      dimension ehigh(0:nebin),emid(nebin) ! higher and middle point of energy bin
      dimension ahigh(0:nabin),amid(nabin) ! higher and middle point of angular bin
      dimension etable(0:nebin)            ! probability table (0.0 for 0, 1.0 for nebin)
      dimension atable(0:nabin,0:nebin)    ! probability table (0.0 for 0, 1.0 for nabin) 
      data IangPart/1,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     &0,0,0,0,4,4,5,5,6/ ! Angular particle ID
      save IangPart,ehigh,emid,ahigh,amid,etable,atable,totalflux

      data kfcode/0/

! Input parameters, if you would like to change the conditions, please revise these parameters
      data r0/100/   ! Radius of Source Surface
      data ip/31/ ! Particle ID (Particle ID, 0:neutron, 1-28:H-Ni, 29-30:muon+-, 31:e-, 32:e+, 33:photon)     
      data iyear/2017/  ! Year
      data imonth/1/    ! Month
      data iday/1/      ! Date
      data glat/33.5d0/   ! Latitude (deg), -90 =< glat =< 90
      data glong/130.5d0/ ! Longitude (deg), -180 =< glong =< 180
      data Alti/0.0d0/   ! Altitude (km)
      data g/0.15d0/      ! Local geometry parameter, 0=< g =< 1: water weight fraction, 10:no-earth, 100:blackhole, -10< g < 0: pilot, g < -10: cabin

! Initialization      
      if(kfcode.eq.0) then ! initialization start
       if(IangPart(ip).eq.0) then
        write(*,*) 'No angular distribution for the particle'
        stop
       endif 
       if(ip.eq.0) then ! neutron
        kfcode=2112
       elseif(ip.eq.1) then ! proton
        kfcode=2212
       elseif(ip.eq.2) then ! alpha
        kfcode=2000004
       elseif(ip.eq.29) then ! muon+
        kfcode=-13
       elseif(ip.eq.30) then ! muon-
        kfcode=13
       elseif(ip.eq.31) then ! electron
        kfcode=11
       elseif(ip.eq.32) then ! positron
        kfcode=-11
       elseif(ip.eq.33) then ! photon
        kfcode=22
       endif
! Set Conditions (location, time, and local geometry)
       s=getHP(iyear,imonth,iday,idummy) ! Solar activity (W index) of the day
       r=getr(glat,glong)                ! Vertical cut-off rigidity (GV)
       d=getd(alti,glat)                 ! Atmospheric depth (g/cm2), set glat = 100 for use US Standard Atmosphere 1976.

! Set energy and angle ranges for generation
       emin = 1 ! Minimum energy of particle
       emax = 1.0e6  ! Maximum energy of particle
       amin = 0   ! Minimum cosine of particle
       amax =  1.00  ! Maximum cosine of particle
       if(ip.eq.0.and.emin.lt.1.0e-8) emin=1.0e-8 ! Minimum energy for neutron is 10 meV
       if(ip.ne.0.and.emin.lt.1.0e-2) emin=1.0e-2 ! Minimum energy for other particle is 10 keV

! Make energy and angle mesh
       elog=log10(emin)
       estep=(log10(emax)-log10(emin))/nebin
       do ie=0,nebin
        ehigh(ie)=10d0**elog
        if(ie.ne.0) emid(ie)=sqrt(ehigh(ie)*ehigh(ie-1))
        elog=elog+estep
       enddo

       astep=(amax-amin)/nabin
       do ia=0,nabin
        ahigh(ia)=amin+astep*ia
        if(ia.ne.0) amid(ia)=(ahigh(ia)+ahigh(ia-1))*0.5
       enddo

! Make probability table (absolute value)
       atable(:,:)=0.0d0 ! initialization
       etable(:)=0.0d0
       do ie=1,nebin
        do ia=1,nabin
         atable(ia,ie)=atable(ia-1,ie)+getSpec(ip,s,r,d,emid(ie),g)*
     &   getSpecAngFinal(iangpart(ip),s,r,d,emid(ie),g,amid(ia))*
     &   (2.0*acos(-1.0))*(ahigh(ia)-ahigh(ia-1)) ! angular integrated value
        enddo
       enddo
       do ie=1,nebin
        etable(ie)=etable(ie-1)+atable(nabin,ie)*(ehigh(ie)-ehigh(ie-1)) ! energy integrated value
       enddo
       TotalFlux=etable(nebin) ! Total Flux (/cm2/s), used for normalization
       write(*,*) 'totfact for converting from (/source) to (/sec) =',
     & TotalFlux*pi*r0**2 ! (/cm2/s) x (cm2) = (/sec)

! Make probability table (normalized to 1)
       do ie=1,nebin
        etable(ie)=etable(ie)/etable(nebin)
        do ia=1,nabin
         atable(ia,ie)=atable(ia,ie)/atable(nabin,ie)
        enddo
       enddo

      endif ! End of initialization

! Start of each source generation
      kf=kfcode ! particle type
      e=getGeneration(ie,nebin,ehigh(0),etable(0))    ! energy
c     cx is cos(theta), where theta = directional angle
      cx=getGeneration(ia,nabin,ahigh(0),atable(0,ie)) ! z direction, -1.0:upward, 0.0:horizontal, 1.0:downward
c     phi is azimuthal angle
      phi  =2.0*pi*unirn(dummy)

  10  xd = (unirn(dummy)-0.5) * 2.0 * r0
      yd = (unirn(dummy)-0.5) * 2.0 * r0
      if(xd**2+yd**2.gt.r0**2) goto 10
      zd = r0

      sx=sqrt(1.0-cx**2)

      x=xd*cx*cos(phi)-yd*sin(phi)+zd*sx*cos(phi)
      y=xd*cx*sin(phi)+yd*cos(phi)+zd*sx*sin(phi)
      z=-xd*sx+zd*cx
      u = -sx*cos(phi)
      v = -sx*sin(phi)
      w = -cx

      wt = 1.0
      time = 0.0
      name = 1

      nc1 = 0
      nc2 = 0
      nc3 = 0
!      write(235,'(10es12.4)') e,x,y,z,u,v,w,wt ! for checking purpose
*-----------------------------------------------------------------------

      return
      end


*-----------------------------------------------------------------------
      function getGeneration(ibin,nbin,high,table)
      implicit real*8 (a-h, o-z)
      dimension high(0:nbin)
      dimension table(0:nbin)

      rand=unirn(dummy) ! random number
      do i=1,nbin-1
       if(rand.le.table(i)) exit
      enddo
      ibin=i ! bin ID

      rand=unirn(dummy) ! random number
      getGeneration=high(ibin-1)*rand + high(ibin)*(1.0d0-rand)

      return

      end

