# ====================================================================
# Create a GitHub Project Board with Kanban workflow
# ====================================================================

$token = $env:GITHUB_TOKEN
$owner = "excellent-1"           # <-- Replace with your GitHub username
$repo  = "ARPAAMS" # <-- Replace with your repo name

$headers = @{
    "Authorization" = "token $token"
    "Accept" = "application/vnd.github.inertia+json"
}

# 1. Create the project board
$projectBody = @{
    name = "ARPAAMS Kanban Board"
    body = "Automated Kanban project board for architecture interview demo."
} | ConvertTo-Json

$project = Invoke-RestMethod `
    -Method POST `
    -Uri "https://api.github.com/repos/$owner/$repo/projects" `
    -Headers $headers `
    -Body $projectBody

$projectId = $project.id
Write-Host "Created project ID: $projectId"

# 2. Add standard Kanban columns
$columns = @("Backlog", "In Progress", "Review", "Done")

foreach ($column in $columns) {
    $columnBody = @{ name = $column } | ConvertTo-Json

    $result = Invoke-RestMethod `
        -Method POST `
        -Uri "https://api.github.com/projects/$projectId/columns" `
        -Headers $headers `
        -Body $columnBody

    Write-Host "Created column: $column (ID $($result.id))"
}

Write-Host "Kanban board setup complete!"
