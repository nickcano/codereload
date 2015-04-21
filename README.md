# codereload
An application which locates address offsets in applications using byte signatures.

Relies on Visual Studio 2008 and Qt4.

**This is an old, dead project. Just an import from my old Google Code account**

## Example .apxml (byte signature) file

	<addresspatterns>
		<address>
			<title value="Health" />
			<type value="address" />
			<pattern value="0xE8, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xE8, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x89, 0x35, 0xFF00, 0xFFFF, 0xFFFF, 0xFFFF, 0x89, 0x1D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x89, 0x3D" />
		</address>
		<address>
			<title value="X Position" />
			<type value="address" />
			<pattern value="0xA1, 0xFD05, 0xFD05, 0xFFFF, 0xFFFF, 0x48, 0x8B, 0x0D, 0xFF00, 0xFFFF, 0xFFFF, 0xFFFF, 0x41, 0x8B, 0x15" />
		</address>
		<address>
			<title value="Hourly Exp" />
			<type value="address" />
			<pattern value="0xE8, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x83, 0xC4, 0x18, 0x89, 0x3D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x89, 0x3D, 0xFF00" />
		</address>
		
		<!-- 	
			0xFFFF is wildcard match (Actually, anything prefixed with 0xFF__ will be wildcard, so the last 2 digits could be used for personal reference or whatever .. but 0xFF00 is reserved)
			0xFF00 matches the start of where our address is in the pattern (defaults to 0-index)
			0xFE02 will match anything less than 2 (0xFE03 less than 3, etc)
			0xFD02 will match anything greater than 2 (0xFD03 greater than 3, etc)
			Anything else can be matched by its actual value
		-->
		<!-- type "data": will give the address the 0xFF00 in the pattern lies at [good for finding a location to place a hook at] -->
		<!-- type "address": will give a 4 byte value read from the address given by "data" [Good for finding constant values in MOV EAX, DWORD PTR:[value] and similar statements] -->
	</addresspatterns>
