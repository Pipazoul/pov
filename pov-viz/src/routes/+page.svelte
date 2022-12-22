<script>
let varName = "NUMBER_9"
let table=[
	[1,1,1,1,0,0,0,1],
	[1,0,0,1,0,0,0,1],
	[1,0,0,1,0,0,0,1],
	[1,0,0,1,0,0,0,1],
	[1,1,1,1,1,1,1,1],

];

let strTable = ""

function updateTable(){
	strTable = "["
	for(let i = 0; i < table.length; i++){
		strTable += "["
		for(let j = 0; j < table[i].length; j++){
			strTable += table[i][j]
			if(j != table[i].length - 1){
				strTable += ","
			}
		}
		strTable += "]"
		if(i != table.length - 1){
			strTable += ","
		}
	}
	strTable += "]"
	table = strTable
}



</script>

<svelte:head>
	<title>Home</title>
	<meta name="description" content="Svelte demo app" />
</svelte:head>

<section>
	<table>
		{#each table as row, a}
			<tr>
				{#each row as cell, i}
					<td>
						<!--If cell is 1 change bg color to black -->
						{#if cell == 1}
							<!-- svelte-ignore a11y-click-events-have-key-events -->
							<div on:click={() => table[a][i] = 0} style="background-color: black; width: 50px; height: 50px;"></div>
						{:else}
							<!-- svelte-ignore a11y-click-events-have-key-events -->
							<div  on:click={() => table[a][i] = 1} style="background-color: white; width: 50px; height: 50px;"></div>
						{/if}
					</td>
				{/each}
			</tr>
		{/each}
	</table>
	<div>
		<h1>Nom de votre forme</h1>
		<input type="text" bind:value={varName} />
		<h1>Copier le code ci dessous </h1>
		<code>int {varName}[] = {table}</code>
		<textarea on:change={() => {}} value={table}></textarea>

	</div>
</section>

<style>
	section {
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		flex: 0.6;
	}

	tr td {
		border: 1px solid black;
		padding: 0;
		margin: 0;
	}
	table {
		transform: rotate(90deg);
	}
</style>
