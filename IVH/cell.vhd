----------------------------------------------------------------------------------
-- Engineer: 
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.math_pack.ALL; -- vysledek z prvniho ukolu


entity cell is
   GENERIC (
      MASK              : mask_t := (others => '1') -- mask_t definovano v baliku math_pack
   );
   Port ( 
      INVERT_REQ_IN     : in   STD_LOGIC_VECTOR (3 downto 0);	--vydani pozadavku na inverzi okolnich bunek
      INVERT_REQ_OUT    : out  STD_LOGIC_VECTOR (3 downto 0);	--prijmuti pozadavku na inverzi
      
      KEYS              : in   STD_LOGIC_VECTOR (4 downto 0); --signaly z klavesnice,smery posunu + inverze
      
      SELECT_REQ_IN     : in   STD_LOGIC_VECTOR (3 downto 0); --signal posunujici vybranou bunky do stran
      SELECT_REQ_OUT    : out  STD_LOGIC_VECTOR (3 downto 0); --signal prijmajici jestli ma byt bunka vybrana
      
      INIT_ACTIVE       : in   STD_LOGIC;		--defaultni nastaveni aktivity bunky
      ACTIVE            : out  STD_LOGIC; --jestli je bunka aktivni !(out)!
      
      INIT_SELECTED     : in   STD_LOGIC; --defaultni nastaveni vyberu bunky
      SELECTED          : out  STD_LOGIC; --jestli aktualne bunka vybrana !(out)!

      CLK               : in   STD_LOGIC;	--hodinovy signal pro synchronizaci
      RESET             : in   STD_LOGIC	--resetovaci signal
   );
end cell;

architecture Behavioral of cell is
  constant IDX_TOP    : NATURAL := 0; -- index sousedni bunky nachazejici se nahore v signalech *_REQ_IN a *_REQ_OUT, index klavesy posun nahoru v KEYS
  constant IDX_LEFT   : NATURAL := 1; -- ... totez        ...                vlevo
  constant IDX_RIGHT  : NATURAL := 2; -- ... totez        ...                vpravo
  constant IDX_BOTTOM : NATURAL := 3; -- ... totez        ...                dole
  
  constant IDX_ENTER  : NATURAL := 4; -- index klavesy v KEYS, zpusobujici inverzi bunky (enter, klavesa 5)
  
  signal ACTIVE_BUFFER : STD_LOGIC;
  signal SELECTED_BUFFER:	STD_LOGIC;
begin
-- Pozadavky na funkci (sekvencni chovani vazane na vzestupnou hranu CLK)
--   pri resetu se nastavi ACTIVE a SELECTED na vychozi hodnotu danou signaly INIT_ACTIVE a INIT_SELECTED
--   pokud je bunka aktivni a prijde signal z klavesnice, tak se bud presune aktivita pomoci SELECT_REQ na dalsi bunky nebo se invertuje stav bunky a jejiho okoli pomoci INVERT_REQ (klavesa ENTER)
--   pokud bunka neni aktivni a prijde signal INVERT_REQ, invertuje svuj stav
--   pozadavky do okolnich bunek se posilaji a z okolnich bunek prijimaji, jen pokud je maska na prislusne pozici v '1'
	ACTIVE <= ACTIVE_BUFFER;
	SELECTED <= SELECTED_BUFFER;

process (CLK)
begin
	if (CLK'event) and (CLK = '1') then
		SELECT_REQ_OUT <= "0000";
		INVERT_REQ_OUT <= "0000";
		if (RESET = '1') then	--reset a inicializace
			ACTIVE_BUFFER <= INIT_ACTIVE;
			SELECTED_BUFFER <= INIT_SELECTED;
		elsif (SELECTED_BUFFER = '1')then
			if ((KEYS and ('1', MASK.bottom, MASK.right, MASK.left, MASK.top)) /= "00000") then
				if ((KEYS and "10000") = "10000") then
					ACTIVE_BUFFER <= NOT ACTIVE_BUFFER;
					INVERT_REQ_OUT <= (MASK.bottom,MASK.right,MASK.left,MASK.top);
				elsif ((KEYS(IDX_TOP) and MASK.top) = '1') then
					SELECT_REQ_OUT(IDX_TOP) <= '1';
					SELECTED_BUFFER <= '0';
				elsif ((KEYS(IDX_LEFT) and MASK.left) = '1') then
					SELECT_REQ_OUT(IDX_LEFT) <= '1';
					SELECTED_BUFFER <= '0';
				elsif ((KEYS(IDX_RIGHT) and MASK.right) = '1') then
					SELECT_REQ_OUT(IDX_RIGHT) <= '1';
					SELECTED_BUFFER <= '0';
				elsif ((KEYS(IDX_BOTTOM) and MASK.bottom) = '1') then
					SELECT_REQ_OUT(IDX_BOTTOM) <= '1';
					SELECTED_BUFFER <= '0';
				end if;
			end if;
		elsif(SELECTED_BUFFER = '0') then
			if ((INVERT_REQ_IN and (MASK.bottom,MASK.right,MASK.left,MASK.top)) /= "0000") then
				ACTIVE_BUFFER <= NOT ACTIVE_BUFFER;
			elsif ((SELECT_REQ_IN and (MASK.bottom,MASK.right,MASK.left,MASK.top)) /= "0000") then
				SELECTED_BUFFER <= '1';
			end if;
		end if;	
	end if;
	
end process;
end Behavioral;

