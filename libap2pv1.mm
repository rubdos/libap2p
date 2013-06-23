<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node COLOR="#000000" CREATED="1371949475013" ID="ID_1925386158" MODIFIED="1371949626404" TEXT="libap2p v1">
<font NAME="SansSerif" SIZE="20"/>
<hook NAME="accessories/plugins/AutomaticLayout.properties"/>
<node COLOR="#0033ff" CREATED="1371949493110" ID="ID_417108599" MODIFIED="1371949626395" POSITION="right" TEXT="Protocol">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1371950511954" ID="ID_1635852447" MODIFIED="1371950515096" TEXT="properties">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1371949544787" ID="ID_1193001895" MODIFIED="1371950531252" TEXT="binary">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1371949654856" ID="ID_1335219202" MODIFIED="1371950531256" TEXT="implements kademlia">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1371949663149" ID="ID_1992831784" MODIFIED="1371950531260" TEXT="encrypted, rsa &gt;= 1024, aes after auth">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1371950485601" ID="ID_1077321625" MODIFIED="1371950531265" TEXT="udp">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1371950558567" ID="ID_536784640" MODIFIED="1371950571821" TEXT="obfuscated? Non-recognisable?">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
<node COLOR="#00b439" CREATED="1371950536405" ID="ID_1542120734" MODIFIED="1371950550401" TEXT="formal description">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1371949501228" ID="ID_820921855" MODIFIED="1371949626399" POSITION="left" TEXT="Class structure">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1371949517895" ID="ID_995309075" MODIFIED="1371949626401" TEXT="namespace libap2p">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1371949531226" ID="ID_1072559367" MODIFIED="1371949626401" TEXT="network">
<font NAME="SansSerif" SIZE="14"/>
<node COLOR="#111111" CREATED="1371949637497" ID="ID_1056317577" MODIFIED="1371949903931" TEXT="vector&lt;k-bucket&gt;"/>
<node COLOR="#111111" CREATED="1371949689034" ID="ID_1784448448" MODIFIED="1371950000861" TEXT="node_lookup"/>
</node>
<node COLOR="#990000" CREATED="1371949539912" HGAP="22" ID="ID_591827256" MODIFIED="1371949765667" TEXT="node : network_object" VSHIFT="8">
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1371949700670" ID="ID_1781025064" MODIFIED="1371949739356" TEXT="network_object">
<font NAME="SansSerif" SIZE="14"/>
<node COLOR="#111111" CREATED="1371949745923" ID="ID_686860734" MODIFIED="1371949752494" TEXT="calculate_distance_to"/>
<node COLOR="#111111" CREATED="1371949772271" ID="ID_1334428843" MODIFIED="1371949782813" TEXT="virtual get_id() = 0;"/>
</node>
<node COLOR="#990000" CREATED="1371949796112" HGAP="26" ID="ID_101973832" MODIFIED="1371950422916" TEXT="dht_entry : network_object">
<font NAME="SansSerif" SIZE="14"/>
<node COLOR="#111111" CREATED="1371950234997" ID="ID_1846984449" MODIFIED="1371950276321" TEXT="bool value_is_local"/>
<node COLOR="#111111" CREATED="1371950283042" ID="ID_809568525" MODIFIED="1371950300221" TEXT="get_value (throws unavailable exception)"/>
<node COLOR="#111111" CREATED="1371950302655" ID="ID_921238937" MODIFIED="1371950466355" TEXT="progress fetch_value() (async, cache it)">
<icon BUILTIN="help"/>
</node>
</node>
<node COLOR="#990000" CREATED="1371949912699" ID="ID_1936371569" MODIFIED="1371949920172" TEXT="k-bucket">
<font NAME="SansSerif" SIZE="14"/>
<node COLOR="#111111" CREATED="1371950027782" ID="ID_1501633451" MODIFIED="1371950040305" TEXT="vector&lt;node_ptr&gt;"/>
<node COLOR="#111111" CREATED="1371950042471" ID="ID_1003142073" MODIFIED="1371950045459" TEXT="k"/>
</node>
<node COLOR="#990000" CREATED="1371950332343" ID="ID_1239329987" MODIFIED="1371950463037" TEXT="progress">
<font NAME="SansSerif" SIZE="14"/>
<icon BUILTIN="help"/>
<node COLOR="#111111" CREATED="1371950336409" ID="ID_1985687804" MODIFIED="1371950361637" TEXT="will follow download progress of a dht_entry"/>
</node>
<node COLOR="#990000" CREATED="1371950368647" HGAP="22" ID="ID_1877834354" MODIFIED="1371950420744" TEXT="managed_dht_entry : dht_entry" VSHIFT="28">
<font NAME="SansSerif" SIZE="14"/>
<node COLOR="#111111" CREATED="1371950380997" ID="ID_785699483" MODIFIED="1371950407653" TEXT="Is split up in different dht_entries"/>
</node>
</node>
</node>
</node>
</map>
