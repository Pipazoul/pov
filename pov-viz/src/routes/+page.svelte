<script>
import { onMount } from "svelte";

let varName = "NUMBER_9"
let table=[
	[1,1,1,1,0,0,0,1],
	[1,0,0,1,0,0,0,1],
	[1,0,0,1,0,0,0,1],
	[1,0,0,1,0,0,0,1],
	[1,1,1,1,1,1,1,1],

];

let ledStrip = [1,1,1,1,0,0,0,1];

let rotate = false;
let rotationSpeed = "0.2";

function updateTable(a,i, val){
	table[a][i] = val;
	ledStrip = table[a];
}

let a = 0;

function loop() {
  ledStrip = table[a];
  a = (a + 1) % table.length;
}

onMount(() => {
  setInterval(loop, 100);
});

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
							<div on:click={() => updateTable(a,i, 0)} style="background-color: black; width: 50px; height: 50px;"></div>
						{:else}
							<!-- svelte-ignore a11y-click-events-have-key-events -->
							<div  on:click={() => updateTable(a,i, 1)} style="background-color: white; width: 50px; height: 50px;"></div>
						{/if}
					</td>
				{/each}
			</tr>
		{/each}
	</table>
	<div class="ledstrip {rotate ? "rotate" : ""}">
		{#each ledStrip as cell, i}
			{#if cell == 1}
				<div style="background-color: black; width: 50px; height: 50px;"></div>
			{:else}
				<div style="background-color: white; width: 50px; height: 50px;"></div>
			{/if}
		{/each}


	</div>
	<div>
		<input type="checkbox" bind:checked={rotate} /> Rotation
		<!--rotation speed-->
		
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
	.ledstrip {
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		flex: 0.6;

	}
	/**Rotation animation*/
	@keyframes rotation {
		from {
			transform: rotate(0deg);
		}
		to {
			transform: rotate(360deg);
		}
	}
	.ledstrip.rotate {
		animation: rotation 0.2s linear infinite;
	}


</style>
