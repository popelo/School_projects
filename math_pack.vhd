--VHDL--FILIP_BEDN�R--xbedna63

library IEEE;
use IEEE.STD_LOGIC_1164.all;

package math_pack is

--d�tov� typ--

  type mask_t is
    record
      top    : std_logic;
      left   : std_logic;
      right  : std_logic;
      bottom : std_logic;
    end record;

function getmask(x,y : natural; COLUMNS, ROWS : natural) return mask_t;

end math_pack;

package body math_pack is

--funkcia pre z�skanie masky--

function getmask(x,y : natural; COLUMNS, ROWS : natural) return mask_t is
  variable mask : mask_t:=(top=>'1', left=>'1', right=>'1', bottom=>'1');
    begin
 ---- okraj----
 
--prv�_stapec--   
      if (x=0) then   
          mask.left := '0' ;
      end if;

--posledn�_stapec--   
      if (x=COLUMNS-1) then    
          mask.right := '0' ;
      end if;

--prv�_riadok--  
      if (y=0) then   
          mask.top := '0' ;
      end if;
      
--posledn�_riadok--
      if (y=ROWS-1) then   
          mask.bottom := '0' ;
      end if;
        
    return mask;
  
  end getmask;

end math_pack;