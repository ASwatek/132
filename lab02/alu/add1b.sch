<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_4" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="b" />
        <signal name="XLXN_13" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <signal name="a" />
        <signal name="XLXN_18" />
        <signal name="ci" />
        <signal name="co" />
        <signal name="r" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_29" />
        <port polarity="Input" name="b" />
        <port polarity="Input" name="a" />
        <port polarity="Input" name="ci" />
        <port polarity="Output" name="co" />
        <port polarity="Output" name="r" />
        <blockdef name="and2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="or3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
        </blockdef>
        <blockdef name="or4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="48" y1="-256" y2="-256" x1="0" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <arc ex="112" ey="-208" sx="192" sy="-160" r="88" cx="116" cy="-120" />
            <line x2="48" y1="-208" y2="-208" x1="112" />
            <line x2="48" y1="-112" y2="-112" x1="112" />
            <line x2="48" y1="-256" y2="-208" x1="48" />
            <line x2="48" y1="-64" y2="-112" x1="48" />
            <arc ex="48" ey="-208" sx="48" sy="-112" r="56" cx="16" cy="-160" />
            <arc ex="192" ey="-160" sx="112" sy="-112" r="88" cx="116" cy="-200" />
        </blockdef>
        <blockdef name="and3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
        </blockdef>
        <block symbolname="and2" name="XLXI_1">
            <blockpin signalname="a" name="I0" />
            <blockpin signalname="ci" name="I1" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_2">
            <blockpin signalname="b" name="I0" />
            <blockpin signalname="ci" name="I1" />
            <blockpin signalname="XLXN_5" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_3">
            <blockpin signalname="b" name="I0" />
            <blockpin signalname="a" name="I1" />
            <blockpin signalname="XLXN_6" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_4">
            <blockpin signalname="XLXN_6" name="I0" />
            <blockpin signalname="XLXN_5" name="I1" />
            <blockpin signalname="XLXN_4" name="I2" />
            <blockpin signalname="co" name="O" />
        </block>
        <block symbolname="or4" name="XLXI_5">
            <blockpin signalname="XLXN_29" name="I0" />
            <blockpin signalname="XLXN_28" name="I1" />
            <blockpin signalname="XLXN_27" name="I2" />
            <blockpin signalname="XLXN_26" name="I3" />
            <blockpin signalname="r" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_6">
            <blockpin signalname="b" name="I0" />
            <blockpin signalname="a" name="I1" />
            <blockpin signalname="ci" name="I2" />
            <blockpin signalname="XLXN_26" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_7">
            <blockpin signalname="b" name="I0" />
            <blockpin signalname="a" name="I1" />
            <blockpin signalname="ci" name="I2" />
            <blockpin signalname="XLXN_27" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_8">
            <blockpin signalname="b" name="I0" />
            <blockpin signalname="a" name="I1" />
            <blockpin signalname="ci" name="I2" />
            <blockpin signalname="XLXN_28" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_9">
            <blockpin signalname="b" name="I0" />
            <blockpin signalname="a" name="I1" />
            <blockpin signalname="ci" name="I2" />
            <blockpin signalname="XLXN_29" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="944" y="416" name="XLXI_2" orien="R0" />
        <instance x="944" y="560" name="XLXI_3" orien="R0" />
        <instance x="1552" y="464" name="XLXI_4" orien="R0" />
        <instance x="960" y="272" name="XLXI_1" orien="R0" />
        <branch name="XLXN_4">
            <wire x2="1552" y1="176" y2="176" x1="1216" />
            <wire x2="1552" y1="176" y2="272" x1="1552" />
        </branch>
        <branch name="XLXN_5">
            <wire x2="1376" y1="320" y2="320" x1="1200" />
            <wire x2="1376" y1="320" y2="336" x1="1376" />
            <wire x2="1552" y1="336" y2="336" x1="1376" />
        </branch>
        <branch name="XLXN_6">
            <wire x2="1552" y1="464" y2="464" x1="1200" />
            <wire x2="1552" y1="400" y2="464" x1="1552" />
        </branch>
        <branch name="b">
            <wire x2="736" y1="496" y2="496" x1="368" />
            <wire x2="944" y1="496" y2="496" x1="736" />
            <wire x2="736" y1="496" y2="992" x1="736" />
            <wire x2="1520" y1="992" y2="992" x1="736" />
            <wire x2="736" y1="992" y2="1408" x1="736" />
            <wire x2="736" y1="1408" y2="1600" x1="736" />
            <wire x2="1520" y1="1600" y2="1600" x1="736" />
            <wire x2="1360" y1="1408" y2="1408" x1="736" />
            <wire x2="1504" y1="1408" y2="1408" x1="1360" />
            <wire x2="944" y1="352" y2="352" x1="736" />
            <wire x2="736" y1="352" y2="496" x1="736" />
            <wire x2="1520" y1="1184" y2="1184" x1="1360" />
            <wire x2="1360" y1="1184" y2="1408" x1="1360" />
        </branch>
        <instance x="2352" y="1216" name="XLXI_5" orien="R0" />
        <instance x="1520" y="1056" name="XLXI_6" orien="R0" />
        <instance x="1520" y="1248" name="XLXI_7" orien="R0" />
        <instance x="1504" y="1472" name="XLXI_8" orien="R0" />
        <instance x="1520" y="1664" name="XLXI_9" orien="R0" />
        <branch name="a">
            <wire x2="624" y1="208" y2="208" x1="400" />
            <wire x2="960" y1="208" y2="208" x1="624" />
            <wire x2="624" y1="208" y2="432" x1="624" />
            <wire x2="944" y1="432" y2="432" x1="624" />
            <wire x2="624" y1="432" y2="928" x1="624" />
            <wire x2="1520" y1="928" y2="928" x1="624" />
            <wire x2="624" y1="928" y2="1120" x1="624" />
            <wire x2="1200" y1="1120" y2="1120" x1="624" />
            <wire x2="1520" y1="1120" y2="1120" x1="1200" />
            <wire x2="1200" y1="1120" y2="1536" x1="1200" />
            <wire x2="1520" y1="1536" y2="1536" x1="1200" />
            <wire x2="624" y1="1120" y2="1344" x1="624" />
            <wire x2="1504" y1="1344" y2="1344" x1="624" />
        </branch>
        <branch name="ci">
            <wire x2="480" y1="144" y2="144" x1="416" />
            <wire x2="960" y1="144" y2="144" x1="480" />
            <wire x2="480" y1="144" y2="288" x1="480" />
            <wire x2="944" y1="288" y2="288" x1="480" />
            <wire x2="480" y1="288" y2="864" x1="480" />
            <wire x2="1520" y1="864" y2="864" x1="480" />
            <wire x2="480" y1="864" y2="1056" x1="480" />
            <wire x2="1520" y1="1056" y2="1056" x1="480" />
            <wire x2="480" y1="1056" y2="1472" x1="480" />
            <wire x2="1072" y1="1472" y2="1472" x1="480" />
            <wire x2="1520" y1="1472" y2="1472" x1="1072" />
            <wire x2="1504" y1="1280" y2="1280" x1="1072" />
            <wire x2="1072" y1="1280" y2="1472" x1="1072" />
        </branch>
        <iomarker fontsize="28" x="416" y="144" name="ci" orien="R180" />
        <iomarker fontsize="28" x="400" y="208" name="a" orien="R180" />
        <iomarker fontsize="28" x="368" y="496" name="b" orien="R180" />
        <branch name="co">
            <wire x2="1840" y1="336" y2="336" x1="1808" />
        </branch>
        <iomarker fontsize="28" x="1840" y="336" name="co" orien="R0" />
        <branch name="r">
            <wire x2="2640" y1="1056" y2="1056" x1="2608" />
        </branch>
        <iomarker fontsize="28" x="2640" y="1056" name="r" orien="R0" />
        <branch name="XLXN_26">
            <wire x2="2352" y1="928" y2="928" x1="1776" />
            <wire x2="2352" y1="928" y2="960" x1="2352" />
        </branch>
        <branch name="XLXN_27">
            <wire x2="2064" y1="1120" y2="1120" x1="1776" />
            <wire x2="2064" y1="1024" y2="1120" x1="2064" />
            <wire x2="2352" y1="1024" y2="1024" x1="2064" />
        </branch>
        <branch name="XLXN_28">
            <wire x2="2080" y1="1344" y2="1344" x1="1760" />
            <wire x2="2080" y1="1088" y2="1344" x1="2080" />
            <wire x2="2352" y1="1088" y2="1088" x1="2080" />
        </branch>
        <branch name="XLXN_29">
            <wire x2="2352" y1="1536" y2="1536" x1="1776" />
            <wire x2="2352" y1="1152" y2="1536" x1="2352" />
        </branch>
    </sheet>
</drawing>