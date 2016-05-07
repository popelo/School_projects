---Filip Bednár--- 
---XBEDNA63---
---IVH 2015/2016---

---library---
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.ALL;
use IEEE.STD_LOGIC_arith.ALL;

---counter---
entity counter is
		port(
				CLK : in std_logic;
				RESET : in std_logic;
				
				NUMBER1 : out std_logic_vector(3 downto 0);
				NUMBER2 : out std_logic_vector(3 downto 0);
				NUMBER3 : out std_logic_vector(3 downto 0)
				);
end counter;

---behavior--- 
architecture Behavioral of counter is
signal cif1,cif2,cif3 : std_logic_vector(3 downto 0);

begin

process(CLK,RESET)

begin

			if RESET = '1' then
				cif1 <= (others => '0');
				cif2 <= (others => '0');
				cif3 <= (others => '0');
			end if ;
		
			if CLK = '1' then
					if ( cif1 = 9 ) and ( cif2 = 9 ) then
							cif1 <= "0000" ;
							cif2 <= "0000" ;
							cif3 <= cif3 + 1 ;
					elsif cif1 = 9 then
							cif1 <= "0000" ;
							cif2 <= cif2 + 1 ;
					elsif (cif2 = 9) and (cif1 < 9) then
							cif1 <= cif1 + 1 ;
					elsif cif2 = 9  then
							cif2 <= "0000" ;
							cif3 <= cif3 + 1 ;
					else	
							cif1 <= cif1 + 1 ;
					end if ;
			end if ;
			
end process ;
		
		NUMBER1 <= cif1 ;
		NUMBER2 <= cif2 ;
		NUMBER3 <= cif3 ;
		
end Behavioral ;



