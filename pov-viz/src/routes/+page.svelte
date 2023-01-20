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
	<div class="ledStrip-Container">
		<h1>Prévisualisation</h1>
		<div class="ledstrip {rotate ? "rotate" : ""}">
			{#each ledStrip as cell, i}
				{#if cell == 1}
					<div class="cell" style="background-color: black;"></div>
				{:else}
					<div class="cell" style="background-color: white;"></div>
				{/if}
			{/each}
		</div>
	</div>
	<div class="ledMatrix-Container">
		<h1>Créateur d'animation</h1>
		<table class="ledMatrix">
			{#each table as row, a}
				<tr>
					{#each row as cell, i}
						<td>
							<!--If cell is 1 change bg color to black -->
							{#if cell == 1}
								<!-- svelte-ignore a11y-click-events-have-key-events -->
								<div on:click={() => updateTable(a,i, 0)} style="background-color: black;"></div>
							{:else}
								<!-- svelte-ignore a11y-click-events-have-key-events -->
								<div  on:click={() => updateTable(a,i, 1)} style="background-color: white;"></div>
							{/if}
						</td>
					{/each}
				</tr>
			{/each}
		</table>
	</div>
	<div class="settings">
		<div>
			<input type="checkbox" bind:checked={rotate} /> Activer Rotation
			<!--rotation speed-->
		</div>

		
		<h1>Nom de votre forme</h1>
		<input type="text" bind:value={varName} />
		<h1>Copier le code ci dessous </h1>
		<code>int {varName}[] = {table}</code>

	</div>
</section>

<style>
	section {
		display: flex;
		flex-wrap: wrap;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		flex: 0.6;
	}

	.ledMatrix-Container {
		height: 700px;
	}

	tr td {
		border: 1px solid black;
		padding: 0;
		margin: 0;
	}

	tr td div {
		width: 4vw;
		height: 4vw;
	}

	.ledStrip-Container {
		padding: 15px;
		height: 700px;
	}

	.ledstrip {
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		flex: 0.6;
		margin-top: 200px;

	}

	.ledstrip .cell {
		width: 4vw;
		height: 4vw;
	}

	code {
		background-color: #f1f1f1;
		border: 1px solid #ccc;
		border-radius: 3px;
		display: block;
		font-family: Consolas, Monaco, 'Andale Mono', 'Ubuntu Mono', monospace;
		font-size: 14px;

		padding: 12px 10px;
		white-space: pre;
		white-space: pre-wrap;
		word-wrap: break-word;
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

	.settings {
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: left;
		flex: 0.4;
		padding: 15px;
		width: 90%;
	}

	/*Below 1407px */
	@media (max-width: 1407px) {
		.ledMatrix-Container {
			height: inherit;
		}
		.ledMatrix {
			margin-top: 0;
		}
		tr td div {
		width:11vw;
		height: 11vw;
		}

		.ledStrip-Container {
			height: inherit;
			height: 500px;
		}

		.ledstrip .cell {
			width: 10vw;
			height: 10vw;
		}
	}


</style>
