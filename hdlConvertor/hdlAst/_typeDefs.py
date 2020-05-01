from enum import Enum
from typing import Dict, Union, Tuple, List
from hdlConvertor.hdlAst._bases import iHdlObj,iHdlObjWithName

HdlTypeStr = str
# Verilog real
HdlTypeFloat = float


class iHdlTypeDef(iHdlObjWithName):
    """
    Base class for definitions of HDL types.

    :note: note that this is not a c-like typedef but the definition of a type itself.
        c-like typedef is described as shown in examples below.
        Equivalent of SystemVerilog/vhdl:

        .. code-block:: systemverilog

            typedef wire [7:0] octet;

        .. code-block:: vhdl

            subtype octet is std_logic_vector(7 downto 0); is

        .. code-block:: python

            HdlVariableDef(name="octet", type=HdlTypeType, value=iHdlExpr(wire[7:0]))

    :note: vhdl arrays types are described as

        .. code-block:: python

            HdlVariableDef("name", HdlTypeType,
               HdlCall(HdlBuiltinFn.INDEX, [type, array size])
    """


class HdlTypeBitsDef(iHdlTypeDef):
    """
    The type which represents bit or bit vector in HDL (std_logic/_vector
    in VHDL, [0:8] in Verilog )

    :ivar ~.msb: index of most significant bit
    :ivar ~.lsb: index of least significant bit
    :ivar ~.signed: True for SV/VDHL signed type, False for unsigned,
        None if not specified (std_logic_vector, wire, reg)
    :ivar ~.bit_order_bigendian: if True in VHDL std_logic_vector(msb downto lsb)
        becomes (msb to lsb)
    :ivar ~.force_vector: if msb==lsb==0 in VHDL this became std_logic
        instead of std_logic_vector(0 downto 0)
    :ivar ~.states: 2 means that each bit can be 0 or 1
        4 - (0, 1, X, Z) (e.g. Verilog wire)
        9 - (0, 1, X, Z, U, W, L, H, -) (e.g. VHDL std_logic)
            'U': uninitialized. This signal hasn't been set yet.
            'X': unknown. Impossible to determine this value/result.
            '0': logic 0
            '1': logic 1
            'Z': High Impedance
            'W': Weak signal, can't tell if it should be 0 or 1.
            'L': Weak signal that should probably go to 0
            'H': Weak signal that should probably go to 1
            '-': Don't care.

    :note: in new designs you should let lsb=0, it is there only for legacy issues
    """
    STD_LOGIC_STATES = 9
    WIRE_STATES = 4
    __slots__ = ["name", "msb", "lsb", "signed", "bit_order_bigendian", "states"]

    def __init__(self, msb, lsb=0, signed=False):
        super(HdlTypeBitsDef, self).__init__()
        self.msb = msb  # type: int
        self.lsb = lsb  # type: int
        self.signed = signed  # type: Optional[bool]
        self.bit_order_bigendian = False  # type: bool
        self.force_vector = True  # type: bool
        self.is_latched = False  # type: bool
        self.states = 2

    def width(self):
        if self.msb >= self.lsb:
            return self.msb - self.lsb
        else:
            return self.lsb - self.msb

    def __hash__(self):
        return hash((self.msb, self.lsb, self.signed, self.is_bigendian))

    def __eq__(self, other):
        return isinstance(other, HdlTypeBitsDef) and (
            self.msb == other.msb
            and self.lsb == other.lsb
            and self.signed == other.signed
            and self.is_bigendian == other.is_bigendian)


class HdlClassType(Enum):
    (
        CLASS,
        STRUCT,  # also vhdl record type
        UNION,
        INTERFACE,
    ) = range(4)


class HdlClassDef(iHdlTypeDef):
    """
    Definition of SystemVerilog class/struct/interface or VHDL record

    :ivar ~.base_types: parent classes for inheritance
    :type ~.base_types: List[iHdlExpr]
    :type type: HdlClassType
    :ivar ~.is_virtual: True for for SV abstract (virtual) classes
    :ivar ~.members: list of members
    :type ~.members: List[HdlVariableDef]

    :note: equivalent of SystemVerilog/vhdl:

        .. code-block:: systemverilog

            typedef struct packed {
                int a;
            } s_name;

        .. code-block:: vhdl

            type s_name is record
                a: integer;
            end record;

        .. code-block:: python

            HdlVariableDef(name="s_name", type=HdlTypeType,
                           value=HdlClassDef(...))

    """
    __slots__ = ["base_types", "is_virtual", "is_packed", "members"]

    def __init__(self):
        super(HdlClassDef, self).__init__()
        self.type = HdlClassType.CLASS
        self.is_virtual = False  # type: bool
        self.is_packed = True  # type: bool
        self.members = []  # type: List[HdlVariableDef]


class HdlEnumDef(iHdlTypeDef):
    """
    Definition of VHDL Enumeration Type or SystemVerilog enum

    :note: name may be None
    :note: equivalent of SystemVerilog/vhdl:

        .. code-block:: systemverilog

            enum { a, b } e_name;

        .. code-block:: vhdl

           type e_name is (a, b);

        .. code-block:: python

            HdlVariableDef(name="e_name", type=HdlTypeType,
                           value=HdlEnumDef("e_name", ["a", "b"]))
    """
    __slots__ = ["name", "values"]

    def __init__(self):
        super(HdlEnumDef, self).__init__()
        self.values = []  # type: List[Tuple[Optional[str], Optional[iHdlExpr]]]
